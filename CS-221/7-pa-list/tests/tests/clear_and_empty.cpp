#include "executable.h"
#include "box.h"
#include <list>

TEST(clear_and_empty) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        size_t sz = i == 0 ? 0 : t.range<size_t>(100);
        
        Memhook mh;

        const int value = t.get<int>();

        List<int> * ll = new List<int>(sz, value);

        auto constructorMemoryAllocations = mh.n_allocs();

        // Each node should be allocated individually
        ASSERT_EQ(sz, ll->size());
        if(sz) {
            ASSERT_EQ(sz + 1, mh.n_allocs());
        }

        
        ASSERT_EQ(!sz, ll->empty());

        ll->clear();
        
        ASSERT_EQ(constructorMemoryAllocations - 1, mh.n_frees());
        ASSERT_EQ(0ULL, ll->size());
        ASSERT_EQ(true,ll->empty());
        ASSERT_EQ(true,ll->begin() == ll->end()); // Checks if head points to tail.

        delete ll;
    }
}


TEST(use_after_clear) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        size_t sz = i == 0 ? 0 : t.range<size_t>(100);
        
        const int value = t.get<int>();

        List<int> ll(sz, value);

        ll.clear();

        std::list<int> gt_ll;

        // 20 is chose arbitrarily
        for (size_t j = 0; j < 20; ++j) {
            int next_push = t.get<int>();
            if (i & 1) {
                ll.push_front(next_push);
                gt_ll.push_front(next_push);
            } else {
                ll.push_back(next_push);
                gt_ll.push_back(next_push);
            }
        }


        for (size_t j = 0; j < 20; ++j) {
            int next_push = t.get<int>();
            if (i & 1) {
                ll.push_back(next_push);
                gt_ll.push_back(next_push);
            } else {
                ll.push_front(next_push);
                gt_ll.push_front(next_push);
            }
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
