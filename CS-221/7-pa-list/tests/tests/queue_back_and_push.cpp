#include "executable.h"
#include "Queue.h"

#include <vector>

TEST(queue_back_and_push) {
    Typegen t;

    for (size_t i = 0; i < TEST_ITER; i++) {
        // Generate a reference vector and create the queue
        const size_t n = t.range(0x999ULL);
        std::vector<int> gt(n);
        t.fill(gt.begin(), gt.end());
        Queue<int> q;

        Memhook mh;

        for (size_t i = 0; i < n; i++) {
            // Use copy push
            q.push(gt[i]);
            // After pushing, the value should be the new back
            ASSERT_EQ(gt[i], q.back());
        }

        // Check that elements were inserted properly
        ASSERT_EQ(n, mh.n_allocs());
        ASSERT_EQ(0ULL, mh.n_frees());
        ASSERT_EQ(n, q.size());
        
    }

    for (size_t i = 0; i < TEST_ITER; i++) {
        // Generate a reference vector and create the queue
        const size_t n = t.range(0x999ULL);
        std::vector<int> gt(n);
        t.fill(gt.begin(), gt.end());
        Queue<int> q;
        // Create a const reference to use the const back
        const Queue<int>& qr = q;

        Memhook mh;

        for (size_t i = 0; i < n; i++) {
            // Uses copy push
            q.push(gt[i]);
            // Uses const reference back
            ASSERT_EQ(gt[i], qr.back());
        }

        // Check that elements were inserted properly
        ASSERT_EQ(n, mh.n_allocs());
        ASSERT_EQ(0ULL, mh.n_frees());
        ASSERT_EQ(n, q.size());
        
    }
}