#include "executable.h"
#include <vector>

TEST(move_operator) {
    Typegen t;

	for(size_t sz = 0; sz < 0xFF; sz++) {        
        Vector<int>      original(sz);
        std::vector<int> gt(sz);
        
        for(size_t i = 0; i < sz; i++)
            original[i] = gt[i] = t.get<int>();

        Memhook mh;
        size_t frees_during_move;
        {
            size_t cpy_sz = t.range<size_t>(0, 9);

            mh.disable();

            Vector<int> moved(cpy_sz);

            for(size_t i = 0; i < cpy_sz; i++)
                moved[i] = t.get<int>();

            size_t original_cap = original.capacity();
            
            mh.enable();

            // force linking of const copy
            moved = std::move(original);

            if(cpy_sz) {
                ASSERT_EQ(1UL, mh.n_frees());
            } else {
                // either is fine, implementation dependent
                ASSERT_TRUE(mh.n_frees() == 0 || mh.n_frees() == 1);
            }

            ASSERT_EQ(0UL, mh.n_allocs());
            frees_during_move = mh.n_frees();

            ASSERT_EQ(sz,           moved.size());
            ASSERT_EQ(original_cap, moved.capacity());

            for(size_t i = 0; i < sz; i++) {
                ASSERT_EQ(gt[i], moved[i]);
            }
        }

        if(sz) {
            ASSERT_EQ(frees_during_move + 1, mh.n_frees());
        } else {
            ASSERT_TRUE(frees_during_move + 1 == mh.n_frees() || frees_during_move == mh.n_frees());
        }
    }
}

TEST(move_operator__self_copy) {
    Typegen t;
    for(size_t sz = 0; sz < 100; sz++) {
        Vector<int>      original(sz);
        std::vector<int> gt(sz);
        
        for(size_t i = 0; i < sz; i++)
            original[i] = gt[i] = t.get<int>();
        
        Memhook mh;

        size_t original_cap = original.capacity();

        original = std::move(original);

        ASSERT_EQ(0UL,          mh.n_allocs());
        ASSERT_EQ(0UL,          mh.n_frees());
        ASSERT_EQ(original_cap, original.capacity());
        ASSERT_EQ(gt.size(),    original.size());

        for(size_t i = 0; i < sz; i++) {
            ASSERT_EQ(gt[i], original[i]);
        }
    }
}