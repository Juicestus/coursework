#pragma once

#include <cstdint>
#include <cstddef>

/*
    Memhooks
    --------

    Memhooks are objects which track memory
    allocations and frees which occur over
    their lifetime. They can be used to
    programmatically test memory allocation
    and deallocation logic. They do this by
    hooking the "new" and "delete" operators,
    allocating larger blocks, and storing metadata
    in hidden regions not visible to the caller.
    
    Example:

    {
        Memhook mh;

        int * i = new int;

        std::cout << mh.n_allocs() << std::endl; // 1
        std::cout << mh.n_frees()  << std::endl; // 0

        delete i;

        std::cout << mh.n_frees() << std::endl; // 1
    } // Memhook is destroyed and stops listening

    ### Interacting with the standard library
    
    Memhooks will track all allocations, even ones
    initiated in the standard library. Although since
    the standard library is subjective to have internal
    policies regarding when it allocates and how many
    bytes it will request so it should not be relied
    upon to test code. One example is short string 
    optimization which stack allocates small string.

    ### Accessing Allocation Info

    Memhooks collect all the following information about each allocation:

    #### Properties of a block

    // An incrementing monotonic counter track which free / delete call
    // caused a particular allocation. These are the sequence numbers
    // for the block.
    uint64_t alloc_seq;
    uint64_t free_seq;
    
    // Size requested by the caller in bytes.
    // Equal to sizeof(type) * num_allocated
    size_t size;

    // Has this block been freed
    bool freed;

    Example:
    {
        Memhook mh;

        int * i = new int;

        std::cout << mh.last_alloc().size << std::endl; // 4

        delete i;

        std::cout << mh.last_free().size << std::endl; // 4
    }

    ### Disabling

    Memhooks can be disabled during their lifetime. If in the
    disabled state, they will not track allocations or frees. 
    However, blocks previously allocated while the memhooks was
    enabled will appear as freed when querying when retrieving
    the actual block since the list of blocks is tracked globally.

    Example:
    {
        Memhook mh;

        int * i = new int;

        mh.disable();

        int * j = new int;
        int * k = new int;

        delete j;
        delete i;

        mh.enable();

        // Because i was allocated while the memhook was enabled
        std::cout << mh.n_allocs() << std::endl; // 1
        // Because the frees occured while the memhook was disabled
        std::cout << mh.n_frees() << std::endl; // 0
        // Because this memhook "saw" the i allocation and it is now
        // free, this method will not throw
        std::cout << mh.last_free().size << std::endl; // 4

        delete k;

        std::cout << mh.n_frees() << std::endl; // 1
    }


    ### Scoped and enabled frees

    Memhooks track any blocks freed or allocated during their
    lifetimes. If a block was allocated before a Memhook is
    instantiated, the Memhook will be still notified when it
    is freed. To differentiate between them, "scoped frees" are
    frees that occur during the hooks lifetimes (e.g. within its
    scope.) "Enabled frees" only count frees for blocks allocated
    while the Memhook was enabled.

    Example:
    {
        int * i = new int;

        {
            Memhook mh;

            delete i;

            std::cout << mh.n_frees() << std::endl; // 1
            std::cout << mh.n_scoped_frees() << std::endl; // 0
            std::cout << mh.n_enabled_frees() << std::endl; // 1
        }
    }

    ### Thread safety

    No, I have a life lol

    ### Limitations

    - Memhooks can only be allocated on the stack (This is
    not a fundamental limitation, see Memhook.cpp.)
    - By default, only 64 memhooks can exist within a program.
    If you want to increase this, set MAX_MEMHOOKS at compile
    time.
    - Can't be used in concert with valgrind since it overrides
    the same operators using the LD_PRELOAD trick
    - Can't currently be used with Address Sanitizer although
    it may be possible with some fiddling.
*/

struct Blk {
    uint64_t alloc_seq;
    uint64_t free_seq;
    size_t size;
    
    private:
    
    uint32_t refcnt;
    
    public:

    bool freed;

    Blk() = delete;
    ~Blk() = delete;

    void * data();
    void  free_data();
    
    void decrement_refcnt();
	void increment_refcnt();
    
    static Blk * alloc(size_t caller_sz);
    static Blk * from_data(void * data);
};

class Memhook {
    Blk ** _blks;
    
    size_t _capacity;
    size_t _size;

    uint64_t _creation_seq;

    size_t _n_allocs;
    size_t _n_frees;
    size_t _n_scoped_frees;
    size_t _n_enabled_frees;

    bool   _disabled;

    void *operator new(size_t size) = delete;

	void nullify(Memhook & dest);
	void copy_primitives(Memhook const & src, Memhook & dest);

    public: 

    Memhook();
    ~Memhook();
    Memhook(Memhook const & other);
    Memhook(Memhook && other);
    Memhook & operator=(Memhook const & other);
    Memhook & operator=(Memhook && other);

    void report_transaction(Blk * blk);

    /*
        API
    */

    // Return the number of blocks currently being tracked
    // Any new called initiated while the Memhook is tracking
    // or any delete call during the Memhooks lifetime is
    // stores in the block list 
    size_t n_blocks() const noexcept { return _size; }
    // Access the blocks directly
    const Blk & operator[](size_t) const;

    // number of allocations (new calls while the memhook was enabled)
    size_t n_allocs() const noexcept { return _n_allocs; }
    // number of frees which occured while the memhook was enabled
    size_t n_frees() const noexcept { return _n_frees; }

    // number of frees which occured while the memhook was BOTH enabled
    // during the allocation AND free
    size_t n_enabled_frees() const noexcept { return _n_enabled_frees; }
    // number of frees which occured during the lifetime of the memhook
    size_t n_scoped_frees() const noexcept { return _n_scoped_frees; }
    
    // block corresponding to the last novel free or delete call
    Blk const &  last_transaction() const;
    // block for the last free call
    Blk const &  last_free() const;
    // block for the last delete call
    Blk const &  last_alloc() const;
    
    // disable the memhook
    void disable() { _disabled = true; }
    // enable the memhook
    void enable()  { _disabled = false; }
    // reset the memhook
    void reset();
};

void operator delete(void * ptr) noexcept;
void operator delete[](void * ptr) noexcept;
void * operator new(std::size_t size);
void * operator new[](std::size_t size);
