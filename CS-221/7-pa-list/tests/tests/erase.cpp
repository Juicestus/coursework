#include <algorithm>
#include <list>
#include "executable.h"

TEST(erase) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {
        const size_t n = t.range(0x999ULL);
        List<int> ll(n);
        std::list<int> gt_ll(n);

        t.fill(gt_ll.begin(), gt_ll.end());
        std::copy(gt_ll.cbegin(), gt_ll.cend(), ll.begin());

        {
            bool gt_walk_reversed = false,
                 walk_reversed = false;
            
            auto gt_pos = gt_ll.begin();
            auto pos = ll.begin();

            while(gt_ll.size() > 0) {
                size_t steps = t.range(gt_ll.size() + 1);
                
                pos =  pace(ll, pos, steps, walk_reversed);
                gt_pos = pace(gt_ll, gt_pos, steps, gt_walk_reversed);

                auto after_erased = pos;
                ++after_erased;

                {
                    Memhook mh;

                    pos = ll.erase(pos);

                    ASSERT_EQ(1ULL, mh.n_frees());
                    ASSERT_EQ(0ULL, mh.n_allocs());
                }

                gt_pos = gt_ll.erase(gt_pos);

                // Return value should point to the element following the erased item
                if(gt_pos != gt_ll.end())
                    ASSERT_EQ(*gt_pos, *pos);

                // Check that the returned iterator is the same as an iterator the
                // next from the previous iterator
                ASSERT_TRUE(after_erased == pos);

                // lists should be consistent
                {
                    ASSERT_EQ(gt_ll.size(), ll.size());

                    auto gt_it = gt_ll.begin();
                    auto it = ll.begin();
                    
                    while(gt_it != gt_ll.end())
                        ASSERT_EQ_(*gt_it++, *it++, "An inconsistency was found when iterating forward");
                    
                    while(gt_it != gt_ll.begin())
                        ASSERT_EQ_(*--gt_it, *--it, "An inconsistency was found when iterating backward");
                }
            }

        }
    }
    
}
