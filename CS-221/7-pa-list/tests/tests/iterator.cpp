
#include "executable.h"
#include <list>
#include <iostream>

TEST(iterator) {
    Typegen t;

    using iter = typename List<int>::iterator;
    using citer = typename List<int>::const_iterator;

    // Check if the interator can initalize to valid memory
    // It should start at nullptr
    {
        size_t constexpr node_sz = sizeof(typename iter::value_type) + 2 * sizeof(void *);
        char VALID_MEM[node_sz];
        memset(VALID_MEM, 0xEE, sizeof(VALID_MEM));

        char ITER_MEM[sizeof(iter)];
        if(sizeof(ITER_MEM) >= sizeof(void *))
            (* (char **) ITER_MEM) = VALID_MEM;
        
        iter * it = new (ITER_MEM) iter;

        char * p = reinterpret_cast<char *>(&(**it));
        ASSERT_EQ(false,VALID_MEM <= p && p <= VALID_MEM + sizeof(VALID_MEM));

        it->~iter();
    }

    for(size_t i = 0; i < TEST_ITER; i++) {
        const size_t n = t.range(0x1ULL, 0x999ULL);
        
        List<int> ll(n);
        std::list<int> gt_ll(n);

        t.fill(gt_ll.begin(), gt_ll.end());
        std::copy(gt_ll.cbegin(), gt_ll.cend(), ll.begin());

        Memhook mh;

        auto it = ll.cbegin();
        auto gt_it = gt_ll.cbegin();

        auto itc = ++ll.cbegin();
        ASSERT_EQ(true, it != itc);
        ASSERT_EQ(false, it != --itc);

        while(gt_it != gt_ll.cend())
            ASSERT_EQ(*(gt_it++), *(it++));
        
        while(gt_it != gt_ll.cbegin())
            ASSERT_EQ(*(--gt_it), *(--it));

        while(gt_it != --gt_ll.cend())
            ASSERT_EQ(*(++gt_it), *(++it));
        
        while(gt_it != ++gt_ll.cbegin())
            ASSERT_EQ(*(--gt_it), *(--it));
        
        gt_it--;
        it--;

        citer it1 = it;
        citer it2 = std::move(it);

        while(it1 != ll.cend()) {
            ASSERT_EQ(true,it1++ == it2++);
            ASSERT_EQ(false, it1 != it2);
            // link operator=(iterator &&)
            std::swap(it1, it2);
        }

        ASSERT_EQ(0UL, mh.n_scoped_frees());
        ASSERT_EQ(0UL, mh.n_allocs());
    }

    {
        struct point {
            int x;
            int y;
        };

        List<point> pt(1);

        auto it = pt.begin();

        it->x = 4;
        it->y = 2;

        ASSERT_EQ(4, it->x);
        ASSERT_EQ(2, it->y);
    }
}
