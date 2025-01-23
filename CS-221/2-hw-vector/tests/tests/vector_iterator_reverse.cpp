#include "executable.h"
#include <vector>

TEST(iterator_reverse) {
    Typegen t;
    using iterator = typename Vector<int>::iterator;

    for(int i = 0; i < 50; i++) {
        size_t sz = t.range<size_t>(1, 0xFFF);
        
        Vector<int> vec(sz);
        std::vector<int> gt(sz);

        for(size_t i = 0; i < sz; i++)
            vec[i] = gt[i] = t.get<int>();

        {
            
            // Test iteration with operator--(int)
            iterator it = vec.end();
            it--;
            for(ssize_t i = sz - 1; i >= 0; i--)
                ASSERT_EQ(gt[i], *(it--));
            
            // The expression --it should have an lvalue (aka return a reference)
            // This allows you to write code as follows:
            // int i = 0;
            // --i %= 5;
            // Not that you ever will...
            --it = vec.end();
            // Test iteration with operator--()
            for(ssize_t i = sz - 1; i >= 0; i--)
                ASSERT_EQ(gt[i], *(--it));
        }
    }
}