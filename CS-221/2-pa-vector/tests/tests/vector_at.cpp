#include "executable.h"
#include <vector>

TEST(at) {
    {
        Typegen t;
        
        for(int i = 0; i < 100; i++) {
            size_t size = t.range<size_t>(0xFFF);
            Vector<double> vec(size);
            std::vector<double> gt(size);
            

            for(size_t i = 0; i < size; i++) {
                double u = t.unit<double>();
                vec.at(i) = u;
                gt.at(i) = u;
            }

            ASSERT_EXCEPTION(vec.at(size), std::out_of_range);
            ASSERT_EXCEPTION(vec.at(-1), std::out_of_range);
            
            for(size_t i = 0; i < size; i++) {
                Vector<double> const & const_vec = vec;
                ASSERT_EQ(gt[i], const_vec.at(i));
                ASSERT_EQ(gt[i], vec.at(i));
            }
        }
    }
}
