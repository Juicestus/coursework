#include "executable.h"

#include <string>
#include <cmath>
#include <memory>
#include <vector>

#include "box.h"

TEST(insert_multiple) {
    Typegen t;

    for(int j = 0; j < 200; j++) {
        size_t sz = t.range<size_t>(1, 0xFF);

        Vector<Box<int>> vec(sz);
        
        using iter = typename Vector<Box<int>>::iterator;
        
        std::vector<Box<int>> gt(sz);
        
        for(size_t i = 0; i < sz; i++) {
            vec[i] = gt[i] = t.get<int>();
        }
        
        int insert_el = t.get<int>();
        ptrdiff_t i = t.range<ptrdiff_t>(0, sz);
        size_t count = t.range<size_t>(0, 0xFF);

        gt.insert(gt.begin() + i, count, insert_el);

        size_t init_cap = vec.capacity();
        {
            Memhook mh;

            iter pos = vec.insert(vec.begin() + i, count, insert_el);
            
            size_t wanted_allocs = 0;
            
            if(sz + count > init_cap) 
                wanted_allocs = std::ceil(std::log2(static_cast<double>(init_cap + count) / static_cast<double>(init_cap)));
            
            // Copy in adds one copy
            wanted_allocs += count + 1;

            ASSERT_EQ(i, static_cast<ptrdiff_t>(pos - vec.begin()));
            ASSERT_LE(wanted_allocs, mh.n_allocs());
        }

        ASSERT_EQ(gt.size(), vec.size());
        
        for(size_t i = 0; i < gt.size(); i++)
            ASSERT_TRUE(*gt[i] == *vec[i]);
    }
}
