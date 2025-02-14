#include "executable.h"
#include <algorithm>
#include <list>

/*
    Tests methods which retrieve or access the 
    front and back of the list
*/

TEST(terminals) {
    Typegen t;

    // Empty lists should appear empty
    {
        List<int> * ll = new List<int>();

        ASSERT_EQ(true,ll->begin() == ll->end());
        ASSERT_EQ(true,ll->cbegin() == ll->cend());

        List<int> const & const_ll = *ll;

        ASSERT_EQ(true,const_ll.begin() == const_ll.end());

        delete ll; 
    }

    for(size_t i = 0; i < TEST_ITER; i++) {
        const size_t n = t.range(0x1ULL, 0x999ULL);
        
        List<int> ll(n);
        std::list<int> gt_ll(n);

        t.fill(gt_ll.begin(), gt_ll.end());
        std::copy(gt_ll.cbegin(), gt_ll.cend(), ll.begin());

        ASSERT_EQ(*gt_ll.begin(), *ll.begin());
        ASSERT_EQ(*--gt_ll.end(), *--ll.end());

        ASSERT_EQ(*gt_ll.cbegin(), *ll.cbegin());
        ASSERT_EQ(*--gt_ll.cend(), *--ll.cend());
        
        const List<int> & const_ll = ll;

        ASSERT_EQ(*gt_ll.cbegin(), *const_ll.begin());
        ASSERT_EQ(*--gt_ll.cend(), *--const_ll.end());

        ASSERT_EQ(gt_ll.front(), const_ll.front());
        ASSERT_EQ(gt_ll.back(), const_ll.back());

        ll.front() = gt_ll.front() = t.get<int>();
        ll.back() = gt_ll.back() = t.get<int>();

        ASSERT_EQ(gt_ll.front(), ll.front());
        ASSERT_EQ(gt_ll.back(), ll.back());

    }
}