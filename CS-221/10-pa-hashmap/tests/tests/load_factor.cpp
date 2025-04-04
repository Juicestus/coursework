#include "executable.h"

TEST(load_factor) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        using Map = UnorderedMap<std::string, double>;
        using value_type = std::pair<std::string, double>;

        size_t n_pairs = t.range(1000ul);

        std::vector<value_type> pairs(n_pairs);
        t.fill(pairs.begin(), pairs.end());

        size_t sz = t.range(100ull);
        Map map(sz);
        size_t n_buckets =  next_greater_prime(sz);

        for(size_t k = 0; k < n_pairs; k++) {
            map.insert(pairs[k]);
            
            float expected_load = static_cast<float>(k + 1)/static_cast<float>(n_buckets);

            ASSERT_EQ(expected_load, map.load_factor());
        }
    }
}
