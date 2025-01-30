#include "executable.h"

TEST(empty) {
    {
        Typegen t;
        size_t sz =  t.range<size_t>(1, 0xFF);
        Vector<int> v(sz);
        
        
        for(size_t i = 0; i < sz; i++)
            v[i] = t.get<int>();

        ASSERT_FALSE(v.empty()); 
    }

    {
        Vector<int> v;

        ASSERT_TRUE(v.empty());
    }
}