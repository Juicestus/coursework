#include "executable.h"
#include <vector>

TEST(end) {
    Typegen t;

    for(int i = 0; i < 50; i++) {
        size_t sz = t.range<size_t>(1, 0xFFF);
        
        std::vector<int> gt(sz);

        for(size_t i = 0; i < sz; i++)
            gt[i] = t.get<int>();
        
        Vector_Basic<int> vec(gt);

        // enforce linking to iterator type
        Vector_Basic<int>::iterator it = vec.end();
        // avoid requiring operator-- at link time
        ASSERT_EQ(gt[gt.size() - 1], *(&*it-1));

    }

    // Verify that iterating from begin to end results in size iterations
    for(int i = 0; i < 50; i++) {
        size_t sz = t.range<size_t>(1, 0xFFF);
        
        std::vector<int> gt(sz);

        for(size_t i = 0; i < sz; i++)
            gt[i] = t.get<int>();
        
        // Push an element to increase capacity
        gt.push_back(t.get<int>());

        Vector_Basic<int> vec(gt);

        // enforce linking to iterator type
        Vector_Basic<int>::iterator end = vec.end();
        size_t count = 0;

        for (Vector_Basic<int>::iterator itr = vec.begin(); itr != end; itr++) {
            count++;
        }

        // Check if the correct number of iterations occur
        ASSERT_EQ(gt.size(), count);

    }

    // Check that begin == end when empty
    std::vector<int> gt;
    Vector_Basic<int> vec(gt);
    Vector_Basic<int>::iterator begin = vec.begin();
    Vector_Basic<int>::iterator end = vec.end();

    ASSERT_EQ(&*begin, &*end);
}
