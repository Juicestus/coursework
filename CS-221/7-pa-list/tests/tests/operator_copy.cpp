#include <algorithm>
#include <list>
#include "executable.h"

TEST(operator_copy) {

    for(size_t i = 0; i < TEST_ITER; i++) {
        Typegen t;

        {
            const size_t n = t.range(0x999ULL);
            const size_t prev_n = t.range(0x999ULL);

            List<int> ll(n);
            std::list<int> gt_ll(n);

            t.fill(gt_ll.begin(), gt_ll.end());
            std::copy(gt_ll.cbegin(), gt_ll.cend(), ll.begin());

            List<int> ll_cpy(prev_n);
            t.fill(ll_cpy.begin(), ll_cpy.end());

            List<int> const & const_ll = ll;

            Memhook mh;
            ll_cpy = const_ll;

            ASSERT_EQ(n, mh.n_allocs());
            ASSERT_EQ(prev_n, mh.n_frees());

            // Check consistency of copy
            {
                ASSERT_EQ(gt_ll.size(), ll_cpy.size());

                auto it = ll_cpy.cbegin();
                auto gt_it = gt_ll.cbegin();

                while(gt_it != gt_ll.cend())
                    ASSERT_EQ_(*gt_it++, *it++, "An inconsistency was found when iterating forward");
                
                while(gt_it != gt_ll.cbegin())
                    ASSERT_EQ_(*--gt_it, *--it, "An inconsistency was found when iterating backward");    
            }

            // Try to mutilate object, should be protected
            Memhook mutilate_mh;
            ll_cpy = ll_cpy;
            ASSERT_EQ(0ULL, mutilate_mh.n_allocs());
            ASSERT_EQ(0ULL, mutilate_mh.n_frees());

            // Check consistency of copy
            {
                ASSERT_EQ(gt_ll.size(), ll_cpy.size());

                auto it = ll_cpy.cbegin();
                auto gt_it = gt_ll.cbegin();

                while(gt_it != gt_ll.cend())
                    ASSERT_EQ_(*gt_it++, *it++, "An inconsistency was found when iterating forward");
                
                while(gt_it != gt_ll.cbegin())
                    ASSERT_EQ_(*--gt_it, *--it, "An inconsistency was found when iterating backward");    
            }
        }
    }
}
