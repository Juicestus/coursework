#include "executable.h"

TEST(constructor) {
	Vector<int> v;
	Memhook mh;
	
	// At least two size_t for tracking physical capacity and logical size.  A pointer must be allocated as well.
	ASSERT_TRUE(sizeof(v) >= (2 * sizeof(size_t) + sizeof(void *)));

	ASSERT_EQ(0UL, v.size());
	ASSERT_EQ(0UL, v.capacity());
	
	// No allocs
	ASSERT_TRUE(mh.n_allocs() == 0);
}