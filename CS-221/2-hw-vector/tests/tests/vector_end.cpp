#include "executable.h"
#include <vector>

TEST(end) {
    Typegen t;

    for(int i = 0; i < 50; i++) {
        size_t sz = t.range<size_t>(1, 0xFFF);
        
        Vector<int> vec(sz);
        std::vector<int> gt(sz);

        for(size_t i = 0; i < sz; i++)
            vec[i] = gt[i] = t.get<int>();
        
        // enforce linking to iterator type
        Vector<int>::iterator it = vec.end();
        // avoid requiring operator-- at link time
        ASSERT_EQ(gt[gt.size() - 1], *(&*it-1));
    }
}