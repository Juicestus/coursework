#include "executable.h"
#include <vector>

TEST(begin) {
    Typegen t;

    for(int i = 0; i < 50; i++) {
        size_t sz = t.range<size_t>(1, 0xFFF);
        
        Vector<int> vec(sz);
        std::vector<int> gt(sz);

        for(size_t i = 0; i < sz; i++)
            vec[i] = gt[i] = t.get<int>();
        
        // enforce linking to iterator type
        Vector<int>::iterator it = vec.begin();
        ASSERT_EQ(gt[0], *it);
    }
}