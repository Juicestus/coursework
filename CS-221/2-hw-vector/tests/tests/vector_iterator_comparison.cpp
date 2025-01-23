#include "executable.h"
#include <vector>

using iter = typename Vector<int>::iterator;

// avoid linking operator += to decrease interal deps
iter advance_to(iter it, size_t n) {
    for(size_t i = 0; i < n; i++)
        it++;
    return it;
}

TEST(iterator_comparision) {
    Typegen t;

    for(int i = 0; i < 50; i++) {
        size_t sz = t.range<size_t>(0xFF, 0xFFF);
        
        size_t idx1 = t.range<size_t>(0, 0xF);
        size_t idx2 = t.range<size_t>(0xF, 0x3F);
        size_t idx3 = t.range<size_t>(0x3F, sz);

        Vector<int> vec(sz);
        std::vector<int> gt(sz);

        for(size_t i = 0; i < sz; i++)
            vec[i] = gt[i] = t.get<int>();

        {
            
            iter const it1  = advance_to(vec.begin(), idx1);
            iter const it2  = advance_to(vec.begin(), idx2);
            iter const it2c = advance_to(vec.begin(), idx2);
            iter const it3  = advance_to(vec.begin(), idx3);
            iter const it3c = advance_to(vec.begin(), idx3);

            // operator==
            ASSERT_TRUE(it2 == it2c);
            ASSERT_TRUE(it2c == it2);
            ASSERT_TRUE(it3 == it3c);
            
            ASSERT_FALSE(it1 == it2);
            ASSERT_FALSE(it2 == it3);
            ASSERT_FALSE(it3 == it1);

            // operator!=
            ASSERT_FALSE(it2 != it2c);
            ASSERT_FALSE(it3 != it3c);

            ASSERT_TRUE(it1 != it2);
            ASSERT_TRUE(it2 != it3);
            ASSERT_TRUE(it1 != it3);

            // operator<
            ASSERT_TRUE(it1 < it2);
            ASSERT_TRUE(it2 < it3);

            ASSERT_FALSE(it1 < it1);
            ASSERT_FALSE(it2 < it2);

            ASSERT_FALSE(it2 < it1);
            ASSERT_FALSE(it3 < it2);


            // operator>
            ASSERT_TRUE(it2 > it1);
            ASSERT_TRUE(it3 > it2);
            ASSERT_TRUE(it3 > it1);

            ASSERT_FALSE(it1 > it2);
            ASSERT_FALSE(it2 > it3);

            ASSERT_FALSE(it1 > it1);
            ASSERT_FALSE(it2 > it2c);

            // operator <=
            ASSERT_TRUE(it2 <= it2c);
            ASSERT_TRUE(it1 <= it2);
            ASSERT_TRUE(it2 <= it3c);
            ASSERT_TRUE(it3c <= it3);

            ASSERT_FALSE(it3 <= it2);
            ASSERT_FALSE(it2 <= it1);

            // operator >=
            ASSERT_TRUE(it3 >= it3c);
            ASSERT_TRUE(it3 >= it3);
            ASSERT_TRUE(it3 >= it2);
            ASSERT_TRUE(it3 >= it1);

            ASSERT_FALSE(it1 >= it3);
            ASSERT_FALSE(it2 >= it3);
        }
    }
}