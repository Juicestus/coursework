#include <algorithm>
#include <list>
#include "executable.h"

TEST(operator_copy_consistency) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {
        const size_t n = t.range(0x3FFULL);
        const size_t prev_n = t.range(0x3FFULL);

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
        
        // insert and remove from list to ensure consistency
        {
            bool gt_walk_reversed = false,
                cpy_walk_reversed = false,
                walk_reversed = false;

            auto gt_pos = gt_ll.begin();
            auto pos = ll.begin();
            auto copy_pos = ll_cpy.begin();

            for(size_t i = 0; i < n; i++) {
                size_t steps = t.range(gt_ll.size() + 1);
                size_t orig_steps = t.range(ll.size() + 1);
                int value = t.get<int>();

                bool should_insert = t.get<bool>(0.50);

                copy_pos = pace(ll_cpy, copy_pos, steps, cpy_walk_reversed);
                gt_pos = pace(gt_ll, gt_pos, steps, gt_walk_reversed);
                pos = pace(ll, pos, orig_steps, walk_reversed);

                if(should_insert || gt_ll.empty() || ll.empty()) {
                    auto it_val = ll_cpy.insert(copy_pos, value);
                    gt_ll.insert(gt_pos, value);
                    ll.insert(pos, value);

                    // return value should point to item
                    ASSERT_EQ(value, *it_val);
                } else {
                    copy_pos = ll_cpy.erase(copy_pos);
                    gt_pos = gt_ll.erase(gt_pos);
                    pos = ll.erase(pos);
                }

                // lists should be consistent
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
}
