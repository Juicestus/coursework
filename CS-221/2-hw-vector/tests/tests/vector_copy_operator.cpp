#include "executable.h"
#include <vector>

TEST(copy_operator) {
    Typegen t;

	for(size_t sz = 0; sz < 0xFF; sz++) {
        std::vector<int> gt(sz);
        
        Memhook mh;
        size_t expected_frees_accumulator = 0;
        mh.disable();
        { 
            Vector<int>      original(sz);
            
            for(size_t i = 0; i < sz; i++)
                original[i] = gt[i] = t.get<int>();
            
            size_t cpy_sz = t.range<size_t>(0, 9);

            Vector<int> copy(cpy_sz);

            for(size_t i = 0; i < cpy_sz; i++)
                copy[i] = t.get<int>();

            size_t original_cap = original.capacity();
            
            Vector<int> const & const_original = original;

            mh.enable();

            // force linking of const copy
            copy = const_original;

            if(cpy_sz) {
                ASSERT_EQ(1UL, mh.n_frees());
            } else {
                // either is fine, implementation dependent
                ASSERT_TRUE(mh.n_frees() == 0 || mh.n_frees() == 1);
            }

            // Already occured
            expected_frees_accumulator += mh.n_frees();

            if(sz) {
                ASSERT_EQ(1UL, mh.n_allocs());
            } else {
                // either is fine, the operator allocs by default when sz=0
                ASSERT_TRUE(mh.n_allocs() == 0 || mh.n_allocs() == 1);
            }

            // Must free this allocation
            expected_frees_accumulator += mh.n_allocs();

            ASSERT_EQ(sz,           copy.size());
            ASSERT_EQ(original_cap, copy.capacity());

            for(size_t i = 0; i < sz; i++) {
                ASSERT_EQ(gt[i], copy[i]);
            }
        }

        // Free the original if nessesary
        if(sz) {
            ASSERT_EQ(expected_frees_accumulator + 1, mh.n_frees());
        } else {
            ASSERT_TRUE(expected_frees_accumulator == mh.n_frees() || expected_frees_accumulator + 1 == mh.n_frees());
        }
    }
}

TEST(copy_operator__self_copy) {
    Typegen t;
    for(size_t sz = 0; sz < 100; sz++) {
        Vector<int>      original(sz);
        std::vector<int> gt(sz);
        
        for(size_t i = 0; i < sz; i++)
            original[i] = gt[i] = t.get<int>();
        
        Memhook mh;

        size_t original_cap = original.capacity();

        original = original;

        ASSERT_EQ(0UL,          mh.n_allocs());
        ASSERT_EQ(0UL,          mh.n_frees());
        ASSERT_EQ(original_cap, original.capacity());
        ASSERT_EQ(gt.size(),    original.size());

        for(size_t i = 0; i < sz; i++) {
            ASSERT_EQ(gt[i], original[i]);
        }
    }
}