#include "executable.h"
#include <vector>

TEST(iterator_io) {
    Typegen t;

    struct xy {
        int x;
        int y;
    };

    using iterator = typename Vector<xy>::iterator;

    for(int i = 0; i < 50; i++) {
        size_t sz = t.range<size_t>(1, 0xFF);
        
        Vector<xy> vec(sz, xy());
        std::vector<xy> gt(sz, xy());

        for(size_t i = 0; i < sz; i++) {
            vec[i] = gt[i] = xy{
                t.get<int>(), t.get<int>()
            };
        }

        {
            
            // Test iterator operator*
            iterator it = vec.begin();
            ASSERT_EQ(gt[0].x, (*it).x);
            ASSERT_EQ(gt[0].y, (*it).y);
            
            // Test iterator operator->
            ASSERT_EQ(gt[0].x, it->x);
            ASSERT_EQ(gt[0].y, it->y);

            // Dereferencing provides a lvalue
            it->x = gt[0].x = t.get<int>();
            (*it).y = gt[0].y = t.get<int>();

            ASSERT_EQ(gt[0].x, it->x);
            ASSERT_EQ(gt[0].y, it->y);

        }
    }
}