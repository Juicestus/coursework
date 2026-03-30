// Physical memory allocator, for user processes,
// kernel stacks, page-table pages,
// and pipe buffers. Allocates whole 4096-byte pages.

#include "types.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "riscv.h"
#include "defs.h"

void freerange(void *pa_start, void *pa_end);

extern char end[]; // first address after kernel.
                   // defined by kernel.ld.

struct run {
  struct run *next;
};

struct {
  struct spinlock lock;
  struct run *freelist;
#ifdef LAB_2
  struct run *hugepages;
#endif
} kmem;

#ifdef LAB_2
static struct stats {
  int npages;
  int nhugepages;
} stats;

int
statskalloc(char *buf, int sz) {
  return snprintf(buf, sz, "%d %d", stats.npages, stats.nhugepages);
}
#endif

void
kinit()
{
  initlock(&kmem.lock, "kmem");
  freerange(end, (void*)PHYSTOP);
}

void
freerange(void *pa_start, void *pa_end)
{
  char *p;
#ifdef LAB_2
  int c;
  p = (char*)HUGEPGROUNDUP((uint64)pa_start);
  for (c = 0; c < MAXHUGEPG && p + HUGEPGSIZE <= (char*)pa_end; p += HUGEPGSIZE, c++)
    kfree_huge(p);
#else
  p = (char*)PGROUNDUP((uint64)pa_start);
#endif
  for(; p + PGSIZE <= (char*)pa_end; p += PGSIZE)
    kfree(p);
#ifdef LAB_2
  stats.npages = 0;
  stats.nhugepages = 0;
#endif
}

// Free the page of physical memory pointed at by pa,
// which normally should have been returned by a
// call to kalloc().  (The exception is when
// initializing the allocator; see kinit above.)
void
kfree(void *pa)
{
  struct run *r;

  if(((uint64)pa % PGSIZE) != 0 || (char*)pa < end || (uint64)pa >= PHYSTOP)
    panic("kfree");

  // Fill with junk to catch dangling refs.
  memset(pa, 1, PGSIZE);

  r = (struct run*)pa;

  acquire(&kmem.lock);
  r->next = kmem.freelist;
  kmem.freelist = r;
#ifdef LAB_2
  stats.npages--;
#endif
  release(&kmem.lock);
}

#ifdef LAB_2
void
kfree_huge(void *pa)
{
  struct run *r;

  if(((uint64)pa % HUGEPGSIZE) != 0 || (char*)pa < end || (uint64)pa >= PHYSTOP)
    panic("kfree");

  // Fill with junk to catch dangling refs.
  memset(pa, 1, HUGEPGSIZE);

  r = (struct run*)pa;

  acquire(&kmem.lock);
  r->next = kmem.hugepages;
  kmem.hugepages = r;
  stats.nhugepages--;
  release(&kmem.lock);
}
#endif

// Allocate one 4096-byte page of physical memory.
// Returns a pointer that the kernel can use.
// Returns 0 if the memory cannot be allocated.
void *
kalloc(void)
{
  struct run *r;

  acquire(&kmem.lock);
  r = kmem.freelist;
  if(r) {
    kmem.freelist = r->next;
#ifdef LAB_2
    stats.npages++;
#endif
  }
  release(&kmem.lock);

  if(r)
    memset((char*)r, 5, PGSIZE); // fill with junk
  return (void*)r;
}

#ifdef LAB_2
void *
kalloc_huge(void)
{
  struct run *r;

  acquire(&kmem.lock);
  r = kmem.hugepages;
  if(r) {
    kmem.hugepages = r->next;
    stats.nhugepages++;
  }
  release(&kmem.lock);

  if(r)
    memset((char*)r, 5, HUGEPGSIZE); // fill with junk
  return (void*)r;
}
#endif
