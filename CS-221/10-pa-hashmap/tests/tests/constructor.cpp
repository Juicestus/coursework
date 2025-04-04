#include "executable.h"

TEST(constructor_default) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {
        size_t n = t.range(10000ull);
        size_t bucket_count = next_greater_prime(n);

        Memhook mh;
        UnorderedMap<int, int> map(n);
        ASSERT_EQ(1ULL, mh.n_allocs());
        ASSERT_EQ(sizeof(void *) * bucket_count, mh.last_alloc().size);

        ASSERT_EQ(0ULL, map.size());
        ASSERT_EQ(bucket_count, map.bucket_count());
    }
}