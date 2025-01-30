#include "pushback_common.h"
#include "executable.h"
#include <vector>
#include "box.h"

TEST(push_back) {
    Typegen t;

    for(int i = 0; i < 100; i++) {
        std::vector<int> gt(last_idx, 0);
        t.fill(gt.begin(), gt.end());

        std::vector<Box<int>> copy_from(last_idx, Box<int>(nullptr));
        
        for(size_t i = 0; i < last_idx; i++)
            copy_from[i] = gt[i];

        {
            Memhook m;

            Vector<Box<int>> vec;
            for(size_t p = 0, idx = 0; p < last_idx;) {
                const Memstate & s = state[idx];
                const size_t expected_allocs = s.n_allocs + p;
                
                m.disable();
                ASSERT_EQ(p,           vec.size());          
                ASSERT_EQ_(s.capacity,  vec.capacity(), "Capacity should double on resize");      
                ASSERT_EQ_(expected_allocs,  m.n_allocs(), "Check that your resizing is memory efficient");        
                ASSERT_EQ(s.n_frees,   m.n_frees());                         
                m.enable();
                
                vec.push_back(copy_from[p]);

                for(size_t i = 0; i < p; i++) {
                    ASSERT_EQ(gt[i], *vec[i]);
                }

                if(state[idx + 1].idx <= ++p)
                    idx++;
            }
        }
    } 
}
