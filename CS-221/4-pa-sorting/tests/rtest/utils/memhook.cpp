#include "memhook.h"

#include <cstdio>
#include <cstdlib>
#include <new>
#include <stdexcept>
#include <cassert>
#include <cstring>

/*
    Implementation notes:

    - A prior version of this used standard library structures to
    track allocations. Since these structures used new and delete
    internally, this resulted in recursive calls within the internal
    tracking logic. While there were boggy solutions to get around
    these, programs would sometimes segfault during teardown. Instead
    of dealing with that this version using C memory handling to
    forgo the problem completely. This also means that all data
    structures have to be written from scratch. 
*/

// xmm registers require 16-byte alignment for (efficient) access
// also don't cross cache boundaries
#define ALIGNMENT_BYTES 16UL
#define ALIGN_TO(n, bytes) ((n + (bytes - 1)) & ~(bytes - 1))

// Global counters
static uint64_t _alloc_seq = 0;
static uint64_t _free_seq  = 0;

/*
    Malloc calls which throw when they run out of memory
    
    Sometimes malloc may return nullptr when size = 0, this
    is accounted for elsewhere
*/
void * xmalloc(size_t size) {
    if(void * ptr = malloc(size))
        return ptr;
    throw std::bad_alloc();
}

void * xrealloc(void * old_ptr, size_t size) {
    if(void * ptr = realloc(old_ptr, size))
        return ptr;
    throw std::bad_alloc();
}

// Allocate a block with enough space for the caller's data
// All blocks are 16-bytes aligned
Blk * Blk::alloc(size_t caller_sz) {
    size_t real_sz = caller_sz ? caller_sz : 1;
    size_t blksz = ALIGN_TO(real_sz + sizeof(Blk), ALIGNMENT_BYTES);
    
    void * ptr = xmalloc(blksz);
    
    if(!ptr)
        return nullptr;

    Blk * header = static_cast<Blk *>(ptr);

    header->alloc_seq = _alloc_seq++;
    header->free_seq = 0;
    header->size = caller_sz;
    header->refcnt = 0;
    header->freed = false;

    return header;
}

// Provided a data point, walk it back the header offset to find the block
Blk * Blk::from_data(void * data) {
    return reinterpret_cast<Blk *>(
        static_cast<char *>(data) - ALIGN_TO(sizeof(Blk), ALIGNMENT_BYTES)
    );
}

// Free the data if there are no memhooks referencing the block
// Does not set the freed boolean or counter since this has to be set
// before the memhooks are notified
void Blk::free_data() {
    if(!refcnt) {
        free(reinterpret_cast<void*>(this)); 
    }
}

// When a memhook de-registers, it decrements the refcnt. When all stop tracking
// a block, it is freed
void Blk::decrement_refcnt() {
	if(!--refcnt && freed)
        free(reinterpret_cast<void*>(this));
}

void Blk::increment_refcnt() {
	refcnt++;
}

// Access the data pointer to be returned to the caller
void * Blk::data() {
    return static_cast<void *>(
        reinterpret_cast<char *>(this) + ALIGN_TO(sizeof(Blk), ALIGNMENT_BYTES)
    );
}


// Hooks can only be stack allocated

// Since the program is not thread safe, we can store them
// in an array.

// A doubly linked list would relax these constraints if someone was willing
// to write one

#ifndef MAX_MEMHOOKS
#define MAX_MEMHOOKS 64
#endif

static Memhook * _live_hooks[MAX_MEMHOOKS];
static size_t    n_hooks = 0;

static void push_hook(Memhook * hook) {
    if(n_hooks >= MAX_MEMHOOKS)
        throw std::logic_error("Too many hooks");

    _live_hooks[n_hooks++] = hook;
}

static void pop_hook(Memhook * hook) {
    if(_live_hooks[n_hooks - 1] == hook) {
        _live_hooks[n_hooks--] = nullptr;
        return;
    }
    throw std::invalid_argument("Memhook allocated invalidly");
}

// Macros for reallocating dynamic arrays

#define REALLOC_ARRAY(x, alloc) xrealloc(static_cast<void*>(x), (alloc) * sizeof(*(x)))
#define REALLOC_NEXT_CAP(x) (((x)+16)*3/2)

Memhook::Memhook()
    : _blks{nullptr}
    , _capacity{0}
    , _size{0}
    , _creation_seq{ _alloc_seq }
    , _n_allocs{0}
    , _n_frees{0}
    , _n_scoped_frees{0}
    , _n_enabled_frees{0}
    , _disabled {false}
{ 
    push_hook(this);
}

Memhook::~Memhook() {

    for(size_t i = 0; i < _size; i++)
        _blks[i]->decrement_refcnt();

    free(_blks);

    pop_hook(this);
}

// Gets rid of "should be initialized in the member initialization list" warning

#define COPY_PRIMITIVES(other) \
	_capacity { other._capacity }, \
	_size { other._size }, \
	_creation_seq { other._creation_seq }, \
	_n_allocs { other._n_allocs }, \
	_n_frees { other._n_frees }, \
	_n_scoped_frees { other._n_scoped_frees }, \
    _n_enabled_frees { other._n_enabled_frees }, \
	_disabled { other._disabled }

void Memhook::copy_primitives(Memhook const & src, Memhook & dest) {
	dest._capacity = src._capacity;
	dest._size = src._size;
	dest._creation_seq = src._creation_seq;
	dest._n_allocs = src._n_allocs;
	dest._n_frees = src._n_frees;
	dest._n_scoped_frees = src._n_scoped_frees;
    dest._n_enabled_frees = src._n_enabled_frees;
	dest._disabled = src._disabled;
}

void Memhook::nullify(Memhook & dest) {
	dest._blks = nullptr;
	dest._capacity = 0;
	dest._size = 0;
	dest._creation_seq = 0;
	dest._n_allocs = 0;
	dest._n_frees = 0;
	dest._n_scoped_frees = 0;
    dest._n_enabled_frees = 0;
	dest._disabled = false;
}

Memhook::Memhook(Memhook const & other) 
	: _blks { nullptr }
	, COPY_PRIMITIVES(other)
{
    _blks = static_cast<Blk**>(REALLOC_ARRAY(other._blks, other._capacity));
}

Memhook::Memhook(Memhook && other)
	: _blks { other._blks }
	, COPY_PRIMITIVES(other)
{
	nullify(other);
}


void Memhook::reset() {
    free(this->_blks);
    nullify(*this);   
}

Memhook & Memhook::operator=(Memhook const & other) {
    if(&other == this)
        return *this;
    
    free(_blks);

    _blks = static_cast<Blk**>(REALLOC_ARRAY(other._blks, other._capacity));
	copy_primitives(other, *this);

    return *this;
}

Memhook & Memhook::operator=(Memhook && other) {
    if(&other == this)
        return *this;

    free(_blks);

    _blks = other._blks;
    copy_primitives(other, *this);
	nullify(other);

    return *this;
}

// Called when blocks are allocated or deleted
void Memhook::report_transaction(Blk * blk) {
    if(_disabled)
        return;
    
    Blk * previous_entry = nullptr;
    for(size_t i = 0; i < _size; i++) {
        if(_blks[i] == blk) {
            previous_entry = _blks[i];
            break;
        }
    }

    if(blk->freed) {
        _n_frees++;

        // The creation sequence number is the first block
        // allocated during the lifetiem of the hook
        // It allows differentiation between scoped frees 
        // and frees
        if(blk->alloc_seq >= _creation_seq)
            _n_scoped_frees++;
        
        if(previous_entry)
            _n_enabled_frees++;
        
    } else {
        _n_allocs++;
    }

    if(previous_entry)
        return;
    
    blk->increment_refcnt();

    if(_size >= _capacity) {
        _capacity = REALLOC_NEXT_CAP(_capacity);
        _blks = static_cast<Blk**>(REALLOC_ARRAY(_blks, _capacity));
    }

    _blks[_size++] = blk;
}

Blk const & Memhook::last_transaction() const {
    if(_size > 0) { return *_blks[_size - 1]; }

    throw std::logic_error("No transactions have occured during the hook's lifetime");
}

Blk const & Memhook::last_alloc() const {
    uint64_t _alloc_seq = 0;
    Blk * blk = nullptr;

    for(size_t i = 0; i < _size; i++) {
        if(_blks[i]->alloc_seq >= _alloc_seq) {
            blk = _blks[i];
            _alloc_seq = _blks[i]->alloc_seq;
        }
    }

    if(blk)
        return *blk;
    
    throw std::logic_error("No allocs occured during the hooks lifetime");
}

Blk const & Memhook::last_free() const {
    uint64_t _free_seq = 0;

    Blk * blk = nullptr;

    for(size_t i = 0; i < _size; i++) {
        if(_blks[i]->free_seq >= _free_seq && _blks[i]->freed) {
            blk = _blks[i];
            _free_seq = _blks[i]->free_seq;
        }
    }

    if(blk)
        return *blk;

    throw std::logic_error("No frees occured during the hooks lifetime");
}

#define MAGIC_DIRTY_HEX 0xDC

static void * hooked_allocate(size_t size) {
    Blk * blk = Blk::alloc(size);

    for(size_t i = 0; i < n_hooks; i++) {
        _live_hooks[i]->report_transaction(blk);
    }

    void * data = blk->data();

    // explicity dirty memory to get uninitalized allocations to fail
    memset(data, MAGIC_DIRTY_HEX, size);

    return blk->data();
}

static void hooked_free(void * ptr) {
    if(!ptr) return;

    Blk * blk = Blk::from_data(ptr);

    assert(!blk->freed && "DOUBLE FREE DETECTED");

    blk->free_seq = _free_seq++;
    blk->freed = true;

    for(size_t i = 0; i < n_hooks; i++) {
        _live_hooks[i]->report_transaction(blk);
    }

    blk->free_data();
}

const Blk & Memhook::operator[](size_t idx) const { return *_blks[idx]; }

void operator delete(void * ptr) noexcept { hooked_free(ptr); }
void operator delete[](void * ptr) noexcept { hooked_free(ptr); }
void * operator new(std::size_t size) { return hooked_allocate(size); }
void * operator new[](std::size_t size) { return hooked_allocate(size); }
