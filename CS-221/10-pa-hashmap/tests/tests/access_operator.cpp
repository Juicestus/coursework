#include "executable.h"

TEST(access_operator) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        
        size_t n_pairs = t.range(1000ul);
        std::vector<std::pair<double, double>> pairs(n_pairs);
        t.fill(pairs.begin(), pairs.end());

        size_t n = t.range(100ull);
        UnorderedMap<double, double> map(n);
        shadow_map<double, double> shadow_map(n);
    
        for(auto const & pair : pairs) {
            shadow_map.insert(pair);
            
            {
                Memhook mh;
                map[pair.first] = pair.second;
                ASSERT_EQ(1ULL, mh.n_allocs());
                ASSERT_EQ(0ULL, mh.n_frees());
            }

            ASSERT_EQ(pair.second, map[pair.first]);

            ASSERT_PAIRS_FOUND_IN_CORRECT_BUCKETS(shadow_map, map);
        }
    }
}