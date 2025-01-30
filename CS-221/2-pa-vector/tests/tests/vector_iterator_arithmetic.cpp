#include "executable.h"
#include <vector>

using iter = typename Vector<int>::iterator;
using diff_t = iter::difference_type;

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
        
        diff_t idx1 = t.range<diff_t>(0, 0xF);
        diff_t idx2 = t.range<diff_t>(0xF, 0x3F);
        diff_t idx3 = t.range<diff_t>(0x3F, sz);

        diff_t idx1r = sz - idx1;
        diff_t idx2r = sz - idx2;

        Vector<int> vec(sz);
        std::vector<int> gt(sz);

        for(size_t i = 0; i < sz; i++)
            vec[i] = gt[i] = t.get<int>();

        {
            
            iter const it1  = advance_to(vec.begin(), idx1);
            iter const it2  = advance_to(vec.begin(), idx2);
            iter const it3  = advance_to(vec.begin(), idx3);

            iter const begin = vec.begin();
            iter const end   = vec.end();
            
            // offset from iterator difference
            ASSERT_EQ(idx2 - idx1, it2 - it1);
            ASSERT_EQ(idx3 - idx1, it3 - it1);

            // iterator + offset
            ASSERT_EQ(gt[idx1], *(begin + idx1));
            ASSERT_EQ(gt[idx2], *(begin + idx2));

            // offset + iterator
            ASSERT_EQ(gt[idx1], *(idx1 + begin));
            ASSERT_EQ(gt[idx2], *(idx2 + begin));

            // iterator - offset
            ASSERT_EQ(gt[idx1], *(end - idx1r));
            ASSERT_EQ(gt[idx2], *(end - idx2r));

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