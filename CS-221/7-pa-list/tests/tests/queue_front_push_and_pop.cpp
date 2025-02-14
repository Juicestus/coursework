#include "executable.h"
#include "Queue.h"

#include <vector>

TEST(queue_front_push_and_pop) {
    Typegen t;

    for (size_t i = 0; i < TEST_ITER; i++) {
        // Generate a reference vector
        const size_t n = t.range(0x999ULL);
        std::vector<int> gt(n);
        t.fill(gt.begin(), gt.end());
        Queue<int> q;

        Memhook mh;

        // Populate queue by pushing elements
        for (size_t i = 0; i < n; i++) {
            // Uses copy push
            q.push(gt[i]);
        }

        // Check that the queue is properly setup
        ASSERT_EQ(n, mh.n_allocs());
        ASSERT_EQ(n, q.size());


        for (size_t i = 0; i < n; i++) {
            // Compare the fronts each time, then pop
            ASSERT_EQ(gt[i], q.front());
            q.pop();
            ASSERT_EQ(n - i - 1, q.size());
        }

        // The queue should have been emptied
        ASSERT_EQ(n, mh.n_frees());
        ASSERT_EQ(0ULL, q.size());
        
    }

    for (size_t i = 0; i < TEST_ITER; i++) {
        // Generate a reference vector
        const size_t n = t.range(0x999ULL);
        std::vector<int> gt(n);
        t.fill(gt.begin(), gt.end());
        Queue<int> q;
        // Create a const reference to use the const front
        const Queue<int>& qr = q;

        Memhook mh;

        // Populate the queue with the reference data
        for (size_t i = 0; i < n; i++) {
            q.push(gt[i]);
        }

        // Check that the queue is properly setup
        ASSERT_EQ(n, mh.n_allocs());
        ASSERT_EQ(n, q.size());

        for (size_t i = 0; i < n; i++) {
            // Uses const reference front to compare
            ASSERT_EQ(gt[i], qr.front());
            q.pop();
            ASSERT_EQ(n - i - 1, q.size());
        }

        // Check that the queue has been emptied
        ASSERT_EQ(n, mh.n_frees());
        ASSERT_EQ(0ULL, q.size());
        
    }
}