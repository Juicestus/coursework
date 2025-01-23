#include "executable.h"
#include <vector>
#include "box.h"

TEST(erase) {
    Typegen t;

    for(int j = 0; j < 100; j++) {
        size_t sz = t.range<size_t>(1, 0xFFF);
        
        Vector<Box<int>> vec(sz);
        std::vector<Box<int>> gt(sz);

        using iter = typename Vector<Box<int>>::iterator;
        
        for(size_t i = 0; i < sz; i++)
            vec[i] = gt[i] = t.get<int>();
        
        ptrdiff_t i = t.range<ptrdiff_t>(0, sz);

        gt.erase(gt.begin() + i);
 
        size_t init_cap = vec.capacity();
        {
            Memhook mh;

            iter pos = vec.erase(vec.begin() + i);
            
            ASSERT_EQ(i, static_cast<ptrdiff_t>(pos - vec.begin()));
            mh.disable();
            ASSERT_EQ_(0UL, mh.n_allocs(), "Make sure that erase is memory efficient");
        }

        ASSERT_EQ(gt.size(), vec.size());
        ASSERT_EQ(init_cap,  vec.capacity());
        
        for(size_t i = 0; i < gt.size(); i++)
            ASSERT_TRUE(gt[i] == vec[i]);
    }
}
