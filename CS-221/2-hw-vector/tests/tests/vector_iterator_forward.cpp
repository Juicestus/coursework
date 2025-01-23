#include "executable.h"
#include <vector>

TEST(iterator_forward) {
    Typegen t;
    using iterator = typename Vector<int>::iterator;

    for(int i = 0; i < 50; i++) {
        size_t sz = t.range<size_t>(1, 0xFFF);
        
        Vector<int> vec(sz);
        std::vector<int> gt(sz);

        // should be default-constructible
        iterator it;
        {
            // iteration with operator++(int) returns a lvalue
            it = vec.begin();
            for(size_t i = 0; i < sz; i++)
                *(it++) = gt[i] = t.get<int>();

            // The expression ++it should have an lvalue (aka return a reference)
            // This allows you to write code as follows:
            // int i = 4;
            // ++i %= 5;
            // Not that you ever will...
            ++it = vec.begin();
            // sequence recoverable
            for(size_t i = 0; i < sz; i++)
                ASSERT_EQ(gt[i], *(it++));

            // Test iteration with operator++()
            it = vec.begin();
            for(size_t i = 0; i + 1 < sz; i++)
                ASSERT_EQ(gt[i + 1], *(++it));
        }
    }
}
