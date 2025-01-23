#include "executable.h"

TEST(pop_back) {
	Typegen t;

    for(size_t i = 0; i < 20; i++) {
		Vector<double> v;
		
		size_t n = t.range<size_t>(1, 0xFFFF);
		for(size_t i = 0; i < n; i++)
			v.push_back(t.unit<double>());
		
		Memhook mh;
	
		size_t sz = v.size();
		size_t cap = v.capacity();
		
		ASSERT_EQ(n, sz);
		
		v.pop_back();
		
		ASSERT_EQ(n - 1, v.size());
		ASSERT_EQ(cap, v.capacity());
		ASSERT_EQ(0UL, mh.n_allocs());
		ASSERT_EQ(0UL, mh.n_frees());
    }
}
