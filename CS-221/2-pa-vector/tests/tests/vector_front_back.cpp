#include "executable.h"

TEST(front_back) {
    {
        Typegen t;

        for(int i = 0; i < 50; i++) {
            size_t sz =  t.range<size_t>(1, 0xFFF);
            Vector<int> vec(sz);
            const Vector<int> & const_vec = vec;
            
            for(size_t i = 0; i < sz; i++)
                vec[i] = t.get<int>();
            
            ASSERT_EQ(sz, vec.size());
            ASSERT_EQ(sz, vec.capacity());

            ASSERT_EQ(vec[0], const_vec.front());
            ASSERT_EQ(vec[0], vec.front());

            ASSERT_EQ(vec[sz - 1], const_vec.back());
            ASSERT_EQ(vec[sz - 1], vec.back());
        }
    }
}