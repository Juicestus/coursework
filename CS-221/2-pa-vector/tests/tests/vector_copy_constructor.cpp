#include "executable.h"
#include <vector>

TEST(copy_constructor) {
    Typegen t;

	for(size_t sz = 0; sz < 0xFF; sz++) {
        Vector<int> original;
        std::vector<int> gt(sz);

        for(size_t i = 0; i < sz; i++) {
            gt[i] = t.get<int>();
            original.push_back(gt[i]);
        }
        
        size_t original_cap = original.capacity();

        {
            // force linking of const copy
            Vector<int> const & const_original = original;

            Memhook mh;

            Vector<int> copy = const_original;

            ASSERT_EQ(original_cap, copy.capacity());
            ASSERT_EQ(sz,           copy.size());
            if (original_cap == 0) {
                ASSERT_GE(1UL,      mh.n_allocs());
            } else {
                ASSERT_EQ(1UL,      mh.n_allocs());
            }
            ASSERT_EQ(0UL,          mh.n_frees());

            for(size_t i = 0; i < sz; i++) {
                ASSERT_EQ(gt[i], copy[i]);
            }

        }
    }
}