#include "executable.h"

TEST(push_and_empty) {
    Typegen t;
    

    for(size_t k = 0; k < TEST_ITER; k++) {
        size_t n = k == 0 ? 0 : t.range(100ull);

        PriorityQueue<int> pq;

        for(size_t i = 0; i < n; i++) {
            pq.push(t.get<int>());
        }

        ASSERT_EQ(pq.empty(), (n == 0));
    }
}