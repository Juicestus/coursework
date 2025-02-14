#include "executable.h"
#include "box.h"

#include <list>
#include <iterator>
#include <iostream>

TEST(insert) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {
        const size_t n = t.range(0x400ULL);

        {
            List<int> * ll = new List<int>();
       
            std::list<int> gt_ll;

            bool gt_walk_reversed = false,
                 walk_reversed = false;
            
            auto gt_pos = gt_ll.cbegin();
            auto pos = ll->cbegin();

            for(size_t i = 0; i < n; i++) {
                size_t steps = t.range(gt_ll.size() + 1);
                int value = t.get<int>();

                pos = pace(*ll, pos, steps, walk_reversed);
                gt_pos = pace(gt_ll, gt_pos, steps, gt_walk_reversed);

                typename List<int>::iterator it_val;
                {
                    Memhook mh;
                    it_val = ll->insert(pos, value);
                    ASSERT_EQ(1ULL, mh.n_allocs());
                }

                gt_ll.insert(gt_pos, value);

                // return value should point to item
                ASSERT_EQ(value, *it_val);

                // lists should be consistent
                {
                    ASSERT_EQ(gt_ll.size(), ll->size());

                    auto gt_it = gt_ll.cbegin();
                    auto it = ll->cbegin();
                    
                    while(gt_it != gt_ll.cend())
                        ASSERT_EQ_(*gt_it++, *it++, "An inconsistency was found when iterating forward");

                    while(gt_it != gt_ll.cbegin())
                        ASSERT_EQ_(*--gt_it, *--it,  "An inconsistency was found when iterating backward");
                }
            }

            delete ll;
        }

        {
            List<Box<int>> ll;

            std::list<int> gt_ll;

            bool gt_walk_reversed = false,
                 walk_reversed = false;
            
            auto gt_pos = gt_ll.cbegin();
            auto pos = ll.cbegin();

            for(size_t i = 0; i < 20; i++) {
                size_t steps = t.range(gt_ll.size() + 1);
                int value = t.get<int>();
                Box<int> newBox = value;

                pos = pace(ll, pos, steps, walk_reversed);
                gt_pos = pace(gt_ll, gt_pos, steps, gt_walk_reversed);

                gt_ll.insert(gt_pos, newBox);
                Memhook mh;
                auto it_val = ll.insert(pos, std::move(newBox));

                ASSERT_EQ(i + 1, ll.size());
                // return value should point to inserted item
                ASSERT_EQ(value, **it_val);
                // only should allocate 1 node on the heap
                ASSERT_EQ(1ULL, mh.n_allocs());

                // lists should be consistent
                {
                    ASSERT_EQ(gt_ll.size(), ll.size());

                    auto gt_it = gt_ll.cbegin();
                    auto it = ll.cbegin();
                    
                    while(gt_it != gt_ll.cend())
                        ASSERT_EQ_(*(gt_it++), *(it++), "An inconsistency was found when iterating forward");

                    while(gt_it != gt_ll.cbegin())
                        ASSERT_EQ_(*(--gt_it), *(--it),  "An inconsistency was found when iterating backward");
                }
            }
        }
    }
    
}
