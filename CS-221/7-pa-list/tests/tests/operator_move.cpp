#include <algorithm>
#include <list>
#include "executable.h"

TEST(operator_move) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {
        {
            const size_t n = i == 0 ? 0 : t.range(0x999ULL);
            const size_t prev_n = t.range(0x999ULL);

            List<int> ll(n);
            std::list<int> gt_ll(n);

            t.fill(gt_ll.begin(), gt_ll.end());
            std::copy(gt_ll.cbegin(), gt_ll.cend(), ll.begin());

            List<int> ll_cpy(prev_n);
            t.fill(ll_cpy.begin(), ll_cpy.end());

            Memhook mh;
            ll_cpy = std::move(ll);
            
            // List object should be in an "empty" state
            #ifndef ALT_LIST_VALID_MOVE_STATE
            // These checks will run by default.
            // Technically, the object only needs to be in a valid state.
            // If you come up with an alternative imp, you may disable this
            // check
            ASSERT_EQ(0ULL, ll.size());
            ASSERT_EQ(true,ll.begin() == ll.end());
            ASSERT_EQ(true,++(--ll.end()) == ll.end());
            #endif

            // Ensure pointers are wired correctly
            // Should handle empty case & stack nodes properly
            ASSERT_EQ(false,++(--ll.end()) == ll_cpy.end());
            ASSERT_EQ(false,++(--ll.end()) == ll_cpy.begin());
            ASSERT_EQ(false,ll.end() == ll_cpy.begin());

            ASSERT_EQ(gt_ll.size(), ll_cpy.size());

            // More explicitly check empty case
            ASSERT_EQ(true,n > 0 || ++(--ll_cpy.end()) == ll_cpy.end());

            // No new allocs and previous memory should have been freed
            ASSERT_EQ(0ULL, mh.n_allocs());
            ASSERT_EQ(prev_n, mh.n_frees());

            {
                // Check consistency of copy
                auto it = ll_cpy.cbegin();
                auto gt_it = gt_ll.cbegin();

                while(gt_it != gt_ll.cend())
                    ASSERT_EQ_(*gt_it++, *it++, "An inconsistency was found when iterating forward");
                
                while(gt_it != gt_ll.cbegin())
                    ASSERT_EQ_(*--gt_it, *--it, "An inconsistency was found when iterating backward");
            }

            // Try to mutilate object, should be protected
            Memhook mutilate_mh;
            ll_cpy = std::move(ll_cpy);
            ASSERT_EQ(0ULL, mutilate_mh.n_allocs());
            ASSERT_EQ(0ULL, mutilate_mh.n_frees());

            {
                // Check consistency of copy
                auto it = ll_cpy.cbegin();
                auto gt_it = gt_ll.cbegin();

                while(gt_it != gt_ll.cend()) {
                    ASSERT_EQ_(*gt_it++, *it++, "An inconsistency was found when iterating forward");
                }
                
                while(gt_it != gt_ll.cbegin())
                    ASSERT_EQ_(*--gt_it, *--it, "An inconsistency was found when iterating backward");
            }
        }
    }
}
