#include "executable.h"

TEST(clear) {
    {
        Typegen t;
        size_t sz =  t.range<size_t>(0xFF);
        Vector<int> v(sz);
        
        
        for(size_t i = 0; i < sz; i++)
            v[i] = t.get<int>();
        
        ASSERT_EQ(sz, v.size());
        ASSERT_EQ(sz, v.capacity());

        v.clear();

        ASSERT_EQ(0UL, v.size());
        ASSERT_EQ(sz,  v.capacity());
    }
}