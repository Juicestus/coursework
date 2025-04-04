#include "executable.h"

TEST(operator_copy) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        using Map = UnorderedMap<double, double>;
        using value_type = std::pair<double, double>;
        
        size_t n_dst_pairs = t.range(1000ul);
        size_t n_src_pairs = t.range(1000ul);

        std::vector<value_type> src_pairs(n_src_pairs);
        t.fill(src_pairs.begin(), src_pairs.end());

        std::vector<value_type> dst_pairs(n_dst_pairs);
        t.fill(dst_pairs.begin(), dst_pairs.end());

        size_t n_src = t.range(100ull);
        size_t n_dst = t.range(100ull);

        Map src_map(n_src);
        Map dst_map(n_dst);

        shadow_map<double, double> src_shad_map(n_src);
        shadow_map<double, double> dst_shad_map(n_dst);

        for(auto const & pair : src_pairs) {
            src_map.insert(pair);
            src_shad_map.insert(pair);
        }

        for(auto const & pair : dst_pairs) {
            dst_map.insert(pair);
            dst_shad_map.insert(pair);
        }

        ASSERT_PAIRS_FOUND_IN_CORRECT_BUCKETS(src_shad_map, src_map);
        ASSERT_PAIRS_FOUND_IN_CORRECT_BUCKETS(dst_shad_map, dst_map);

        {
            Memhook mh;

            dst_map = src_map;

            ASSERT_EQ(dst_shad_map.size() + 1, mh.n_frees());
            ASSERT_EQ(src_shad_map.size() + 1, mh.n_allocs());
            ASSERT_EQ(src_shad_map.size(), dst_map.size());
            ASSERT_EQ(src_shad_map.bucket_count(), dst_map.bucket_count());
        }

        ASSERT_PAIRS_FOUND_IN_CORRECT_BUCKETS(src_shad_map, dst_map);
        ASSERT_PAIRS_FOUND_IN_CORRECT_BUCKETS(src_shad_map, src_map);

        size_t n_new_dst_pairs = t.range(1000ul);
        size_t n_new_src_pairs = t.range(1000ul);

        std::vector<value_type> new_src_pairs(n_new_src_pairs);
        t.fill(new_src_pairs.begin(), new_src_pairs.end());

        std::vector<value_type> new_dst_pairs(n_new_dst_pairs);
        t.fill(new_dst_pairs.begin(), new_dst_pairs.end());

        shadow_map<double, double> new_dst_shad_map = src_shad_map;

        for(auto const & pair : new_dst_pairs) {
            dst_map.insert(pair);
            new_dst_shad_map.insert(pair);
        }

        ASSERT_PAIRS_FOUND_IN_CORRECT_BUCKETS(new_dst_shad_map, dst_map);

        for(auto const & pair : new_src_pairs) {
            src_shad_map.insert(pair);
            src_map.insert(pair);
        }

        ASSERT_EQ(src_shad_map.size(), src_map.size());
        ASSERT_PAIRS_FOUND_IN_CORRECT_BUCKETS(src_shad_map, src_map);
    }
}