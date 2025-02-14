#include <algorithm>
#include <list>
#include "executable.h"

TEST(pop_front) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {
        const size_t n = t.range(0x999ULL);
        List<int> ll(n);
        std::list<int> gt_ll(n);

        t.fill(gt_ll.begin(), gt_ll.end());
        std::copy(gt_ll.cbegin(), gt_ll.cend(), ll.begin());

        {
            while(gt_ll.size() > 0) {
                gt_ll.pop_front();
                
                {
                    Memhook mh;
                    
                    ll.pop_front();

                    // Should free one node
                    ASSERT_EQ(1ULL, mh.n_frees());
                    ASSERT_EQ(0ULL, mh.n_allocs());
                }

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
