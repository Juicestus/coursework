#include "box.h"
#include "executable.h"

#include <unordered_map>


TEST(insert_and_move) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        using iter = typename UnorderedMap<int, Box<int>>::iterator;
        
        size_t n_pairs = t.range(1000ul);
        std::vector<std::pair<int, int>> pairs(n_pairs);
        t.fill_unique(pairs.begin(), pairs.end());

        std::vector<std::pair<int, Box<int>>> boxes(n_pairs);
        std::vector<std::pair<int, Box<int>>> cpy_boxes(n_pairs);

        for(size_t i = 0; i < pairs.size(); i++) {
            auto const & [key, val] = pairs[i];

            boxes[i] = std::make_pair(key, Box<int>(val));
            cpy_boxes[i] = std::make_pair(key, Box<int>(val));
        }

        size_t n = t.range(100ull);
        UnorderedMap<int, Box<int>> map(n);
        shadow_map<int, Box<int>> shadow_map(n);
    
        for(size_t i = 0; i < pairs.size(); i++) {
            auto [it, inserted] = shadow_map.insert(boxes[i]);
            
            std::pair<iter, bool> ret;
            
            {
                Memhook mh;
                ret = map.insert(std::move(cpy_boxes[i]));
                ASSERT_EQ(inserted, mh.n_allocs());
                ASSERT_EQ(0ULL, mh.n_frees());
            }

            ASSERT_EQ(inserted, ret.second);
            ASSERT_EQ(pairs[i].first, ret.first->first);

            ASSERT_PAIRS_FOUND_IN_CORRECT_BUCKETS(shadow_map, map);
        }
    }
}
