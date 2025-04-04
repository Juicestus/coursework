#include "executable.h"

TEST(clear_and_empty) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        using value_type = std::pair<double, double>;
        using Map = UnorderedMap<double, double>;
        
        size_t n = i == 0 ? 0ULL : t.range<size_t>(1, 256);
        size_t n_pairs = t.range(1000ul);
        
        std::vector<value_type> pairs(n_pairs);
        t.fill(pairs.begin(), pairs.end());

        Map map(n);
        shadow_map<double, double> shad_map(n);

        for(auto const & pair : pairs) {
            shad_map.insert(pair);
        }
        
        {
            Memhook mh;
            for(auto const & pair : pairs) {
                map.insert(pair);
            }
            ASSERT_PAIRS_FOUND_IN_CORRECT_BUCKETS(shad_map, map);
            ASSERT_EQ(shad_map.size(), map.size());
            ASSERT_EQ(shad_map.size(), mh.n_allocs());
        }
        
        if(shad_map.size()) ASSERT_FALSE(map.empty());

        {
            Memhook mh;
            map.clear();
            ASSERT_EQ(shad_map.size(), mh.n_frees());
        }
        ASSERT_EQ(0ULL, map.size());
        ASSERT_TRUE(map.empty());
    }
}
