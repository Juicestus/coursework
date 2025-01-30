#include "executable.h"
#include <vector>
#include "box.h"

TEST(erase_multiple) {
    Typegen t;

    for(int k = 0; k < 100; k++) {
        size_t sz = t.range<size_t>(1, 0xFFF);
        
        Vector<Box<int>> vec(sz, 10);
        std::vector<Box<int>> gt(sz, 10);

        using iter = typename Vector<Box<int>>::iterator;
        
        for(size_t i = 0; i < sz; i++)
            vec[i] = gt[i] = t.get<int>();
        
        ptrdiff_t i = t.range<ptrdiff_t>(0, sz - 1);
        ptrdiff_t j = t.range<ptrdiff_t>(i, sz);

        gt.erase(gt.begin() + i, gt.begin() + j);
 
        size_t init_cap = vec.capacity();
        {
            Memhook mh;

            iter pos = vec.erase(vec.begin() + i, vec.begin() + j);
            
            ASSERT_EQ(i, static_cast<ptrdiff_t>(pos - vec.begin()));
            mh.disable();
            ASSERT_EQ_(0UL, mh.n_allocs(), "Make sure that erase multiple is memory efficient");
        }

        ASSERT_EQ(gt.size(), vec.size());
        ASSERT_EQ(init_cap,  vec.capacity());
        
        for(size_t i = 0; i < gt.size(); i++)
            ASSERT_TRUE(gt[i] == vec[i]);
    }
}
