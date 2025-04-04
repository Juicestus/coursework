#include "executable.h"
#include "map_logic.h"

TEST(bucket) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {
        size_t n = t.range(1000ull);
        using Map = UnorderedMap<std::string, int>;
        Map map(n);
        using size_type = typename Map::size_type;
        size_type bucket_count = next_greater_prime(n);
        
        for(size_t i = 0; i < 100; i++) {
            std::string key = t.get<std::string>();

            ASSERT_EQ(correct_bucket<Map>(key, bucket_count), map.bucket(key));
        }
    }
}