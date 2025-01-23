#include "pushback_common.h"
#include "executable.h"
#include <vector>
#include "box.h"

TEST(push_back_move) {
    Typegen t;

    for(int i = 0; i < 100; i++) {
        std::vector<int> gt(last_idx, 0);
        t.fill(gt.begin(), gt.end());

        std::vector<Box<int>> move_from(last_idx, Box<int>(nullptr));
        
        for(size_t i = 0; i < last_idx; i++)
            move_from[i] = gt[i];

        {
            Memhook m;

            Vector<Box<int>> vec;
            for(size_t p = 0, idx = 0; p < last_idx;) {
                const Memstate & s = state[idx];
                
                ASSERT_EQ(p,           vec.size());          
                ASSERT_EQ(s.capacity,  vec.capacity());      
                ASSERT_EQ(s.n_allocs,  m.n_allocs());        
                ASSERT_EQ(s.n_frees,   m.n_frees());                         
                
                vec.push_back(std::move(move_from[p]));

                for(size_t i = 0; i < p; i++) {
                    ASSERT_EQ(gt[i], *vec[i]);
                }

                if(state[idx + 1].idx <= ++p)
                    idx++;
            }
        }
    }
}
