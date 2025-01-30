#include "executable.h"
#include <vector>

TEST(access_operator) {
    Typegen t;
    
    for(size_t i = 0; i < 100; i++) {
        size_t count = t.range<size_t>(0xFFFF);
        std::vector<unsigned int> gt(count);
        
        Memhook m;
        {
            Vector<unsigned int> vec(count);

            for(size_t i = 0; i < count; i++) {
                unsigned int el = t.range<unsigned int>(0xFFFF);
                
                vec[i] = el;
                gt[i] = el;
            }

            for(size_t i = 0; i < count; i++) {
                // Ensure linkage for the const access operator
                const Vector<unsigned int> & const_vec = vec;
                unsigned int el = const_vec[i];
                ASSERT_EQ(gt[i], el);
            }

            ASSERT_EQ(count, vec.size());
            ASSERT_EQ(count, vec.capacity());
        }

        ASSERT_EQ(1UL, m.n_allocs());
        ASSERT_EQ(1UL, m.n_frees());
    }
}