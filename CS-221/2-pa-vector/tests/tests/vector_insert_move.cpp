#include "executable.h"

#include <string>
#include <vector>

#include "box.h"

TEST(insert_move) {
    Typegen t;

    for(int j = 0; j < 100; j++) {
        size_t sz = t.range<size_t>(1, 0xFFF);
        
        Vector<Box<int>> vec(sz);
        
        using iter = typename Vector<Box<int>>::iterator;

        std::vector<Box<int>> gt(sz);
    
        for(size_t i = 0; i < sz; i++)
            vec[i] = gt[i] = t.get<int>();
        
        Box<int> insert_el = t.get<int>();
        ptrdiff_t i = t.range<ptrdiff_t>(0, sz);

        gt.insert(gt.begin() + i, insert_el);
 
        size_t init_cap = vec.capacity();
        {
            Memhook mh;

            iter pos = vec.insert(vec.begin() + i, std::move(insert_el));
            
            ASSERT_EQ(i, static_cast<ptrdiff_t>(pos - vec.begin()));
            ASSERT_EQ(static_cast<size_t>(sz == init_cap), mh.n_allocs());
        }

        ASSERT_EQ(gt.size(), vec.size());
        ASSERT_EQ(init_cap == sz ? 2 * init_cap : init_cap, vec.capacity());
        
        for(size_t i = 0; i < gt.size(); i++)
            ASSERT_TRUE(*gt[i] == *vec[i]);
    }
}
