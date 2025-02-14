#include "executable.h"
#include "Queue.h"

#include <vector>

TEST(queue_push_pop_and_empty) {
    Typegen t;

    for (size_t i = 0; i < TEST_ITER; i++) {
        // Generate a reference vector
        const size_t n = t.range(0x999ULL);
        std::vector<int> gt(n);
        t.fill(gt.begin(), gt.end());
        Queue<int> q;

        Memhook mh;

        // Queue should be empty when first initialized
        ASSERT_EQ(true, q.empty());

        // Populate queue by pushing elements
        for (size_t i = 0; i < n; i++) {
            // Uses copy push
            q.push(gt[i]);
        }

        // Queue should no longer be empty
        ASSERT_EQ(false, q.empty());
        ASSERT_EQ(n, q.size());
        
        // Empty the queue
        for (size_t i = 0; i < n; i++) {
            q.pop();
        }

        // Queue should once again be empty
        ASSERT_EQ(true, q.empty());
        ASSERT_EQ(0ULL, q.size());
    }
}