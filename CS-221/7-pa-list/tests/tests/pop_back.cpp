#include <algorithm>
#include <list>
#include "executable.h"

TEST(pop_back) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {
        const size_t n = t.range(0x999ULL);
        List<int> ll(n);
        std::list<int> gt_ll(n);

        t.fill(gt_ll.begin(), gt_ll.end());
        std::copy(gt_ll.cbegin(), gt_ll.cend(), ll.begin());

        {
            while(gt_ll.size() > 0) {
                gt_ll.pop_back();

                {
                    Memhook mh;

                    ll.pop_back();

                    // Should free one node
                    ASSERT_EQ(1ULL, mh.n_frees());
                    ASSERT_EQ(0ULL, mh.n_allocs());
                }

                // lists should be consistent
                {
                    ASSERT_EQ(gt_ll.size(), ll.size());

                    auto gt_it = gt_ll.begin();
                    auto it = ll.begin();
                    // Iterate forward through the List to ensure the begin(), end(), and operator++()
                    // and operator*() functions operate correctly. The correct ordering should result
                    // from pop back.
                    while(gt_it != gt_ll.end())
                        ASSERT_EQ(*gt_it++, *it++);

                    // Do the same in reverse
                    while(gt_it != gt_ll.begin())
                        ASSERT_EQ(*--gt_it, *--it);
                }
            }

        }
    }
    
}
