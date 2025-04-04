#include "executable.h"
#include <unordered_map>

TEST(erase) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        size_t n_pairs = t.range(1000ul);
        std::vector<std::pair<double, double>> pairs(n_pairs);
        t.fill_unique(pairs.begin(), pairs.end());

        size_t n = t.range(100ull);
        UnorderedMap<double, double> map(n);
        shadow_map<double, double>   gt_map(n);

        std::vector<std::pair<double, double>> cpy_pairs = pairs;
        for(auto const & pair : cpy_pairs) {
            map.insert(pair);
            gt_map.insert(pair);
        }

        t.shuffle(pairs.begin(), pairs.end());

        using Map = UnorderedMap<double, double>;
        using size_type = typename Map::size_type;

        for(auto const & pair : pairs) {
            size_type n_erased;
            {
                Memhook mh;
                n_erased = map.erase(pair.first);
                ASSERT_EQ(0ULL, mh.n_allocs());
                ASSERT_EQ(1ULL, mh.n_frees());
            }

            gt_map.erase(pair.first);

            ASSERT_EQ(1ULL, n_erased);
            ASSERT_EQ(gt_map.size(), map.size());

            ASSERT_PAIRS_FOUND_IN_CORRECT_BUCKETS(gt_map, map);
        }
    }
}
