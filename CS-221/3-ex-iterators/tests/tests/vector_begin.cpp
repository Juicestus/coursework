#include "executable.h"
#include <vector>

TEST(begin) {
    Typegen t;

    for(int i = 0; i < 50; i++) {
        size_t sz = t.range<size_t>(1, 0xFFF);
        
        std::vector<int> gt(sz);

        for(size_t i = 0; i < sz; i++)
            gt[i] = t.get<int>();

        Vector_Basic<int> vec(gt);
        
        // enforce linking to iterator type
        Vector_Basic<int>::iterator it = vec.begin();
        ASSERT_EQ(gt[0], *it);
    }
}
