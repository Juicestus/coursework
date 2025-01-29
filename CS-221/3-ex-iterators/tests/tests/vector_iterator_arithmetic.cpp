#include "executable.h"
#include <vector>

using iter = typename Vector_Basic<int>::iterator;

// avoid linking operator += to decrease interal deps
iter advance_to(iter it, size_t n) {
    for(size_t i = 0; i < n; i++)
        it++;
    return it;
}

TEST(iterator_arithmetic) {
    Typegen t;

    for(int i = 0; i < 0x3FF; i++) {
        size_t sz = t.range<size_t>(0xFF, 0xFFF);
        
        ptrdiff_t idx1 = t.range<ptrdiff_t>(0, 0xF);
        ptrdiff_t idx2 = t.range<ptrdiff_t>(0xF, 0x3F);
        ptrdiff_t idx3 = t.range<ptrdiff_t>(0x3F, sz);

        std::vector<int> gt(sz);

        for(size_t i = 0; i < sz; i++)
            gt[i] = t.get<int>();

        Vector_Basic<int> vec(gt);

        {
            
            iter const it1  = advance_to(vec.begin(), idx1);
            iter const it2  = advance_to(vec.begin(), idx2);
            iter const it3  = advance_to(vec.begin(), idx3);

            iter const begin = vec.begin();
            
            // offset from iterator difference
            ASSERT_EQ(idx2 - idx1, it2 - it1);
            ASSERT_EQ(idx3 - idx1, it3 - it1);

            // iterator + offset
            ASSERT_EQ(gt[idx1], *(begin + idx1));
            ASSERT_EQ(gt[idx2], *(begin + idx2));

            // iterator - offset
            ASSERT_EQ(gt[idx1], *(vec.end() - (sz - idx1)));
            ASSERT_EQ(gt[idx2], *(vec.end() - (sz - idx2)));

            // operator[offset]
            begin[idx1] = gt[idx1] = t.get<int>();
            begin[idx2] = gt[idx2] = t.get<int>();

            ASSERT_EQ(begin[idx1], gt[idx1]);
            ASSERT_EQ(begin[idx2], gt[idx2]);


            // iterator += offset
            {
                iter it = vec.begin();
                it += idx1;
                ASSERT_EQ(gt[idx1], *it1);
            }

            {
                iter it = vec.begin();
                it += idx2;
                ASSERT_EQ(gt[idx2], *it2);
            }

            // iterator -= offset
            {
                iter it = vec.end();
                it -= (sz - idx3);
                ASSERT_EQ(gt[idx3], *it3);
            }

            {
                iter it = vec.end();
                it -= (sz - idx2);
                ASSERT_EQ(gt[idx2], *it2);
            }

        }
    }
}