#include <algorithm>
#include <list>
#include "executable.h"

TEST(constructor_copy) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {
        Memhook mh_mem_loss;

        {
            const size_t n = t.range(0x999ULL);
            List<int> ll(n);
            std::list<int> gt_ll(n);

            t.fill(gt_ll.begin(), gt_ll.end());
            std::copy(gt_ll.cbegin(), gt_ll.cend(), ll.begin());

            List<int> const & const_ll = ll;

            Memhook mh;
            List<int> ll_cpy = const_ll;
            

            ASSERT_EQ(gt_ll.size(), ll_cpy.size());

            ASSERT_EQ(n, mh.n_allocs());
            ASSERT_EQ(0ULL, mh.n_frees());

            auto it = ll_cpy.cbegin();
            auto gt_it = gt_ll.cbegin();

            while(gt_it != gt_ll.cend())
                ASSERT_EQ(*gt_it++, *it++);
            
            while(gt_it != gt_ll.cbegin())
                ASSERT_EQ(*--gt_it, *--it);
        }

        // No memory should be lost
        ASSERT_EQ(mh_mem_loss.n_frees(), mh_mem_loss.n_allocs());
    }
}