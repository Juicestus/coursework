#include "executable.h"
#include "Queue.h"

#include <vector>
#include <queue>

std::queue<int> q;

TEST(queue_equality_operator) {
    Typegen t;

    for (size_t i = 0; i < TEST_ITER; i++) {
        // Generate a reference vector
        const size_t n = t.range(10ULL, 0x999ULL);
        std::vector<int> gt_1(n);
        t.fill(gt_1.begin(), gt_1.end());

        // Checking two equivalent queues
        Queue<int> q1;
        Queue<int> q2;

        {
            Memhook mh;

            // Populate the queues with the refernce vector data
            for (size_t j = 0; j < n; j++) {
                q1.push(gt_1[j]);
                q2.push(gt_1[j]);
            }

            // Check that the queues were properly setup
            ASSERT_EQ(gt_1.size(), q1.size());
            ASSERT_EQ(gt_1.size(), q2.size());
            ASSERT_EQ(2 * n, mh.n_allocs());
        }

        // The queues should have the same data
        {
            Memhook mh;
            ASSERT_EQ(true, q1 == q2);
            // Check that comparison does not allocate extra memory
            ASSERT_EQ(0ULL, mh.n_allocs());
        }

        // Generate a different reference vector
        std::vector<int> gt_2(n);
        t.fill(gt_2.begin(), gt_2.end());

        Queue<int> q3;

        {
            Memhook mh;

            // Populate the queue with the reference vector data
            for (size_t j = 0; j < n; j++) {
                q3.push(gt_2[j]);
            }

            // Ensure that the queue was properly setup
            ASSERT_EQ(gt_2.size(), q3.size());
            ASSERT_EQ(n, mh.n_allocs());
        }

        // The queues should be different
        {
            Memhook mh;
            ASSERT_EQ(false, q1 == q3);
            ASSERT_EQ(false, q3 == q2);
            // Check that comparison does not allocate extra memory
            ASSERT_EQ(0ULL, mh.n_allocs());
        }

        // Comparisons between queues of different sizes should be false
        // Generate a smaller reference vector
        const size_t n_smaller = t.range(0UL, n - 1);
        std::vector<int> gt_3(n_smaller);
        t.fill(gt_3.begin(), gt_3.end());

        Queue<int> q4;

        {
            Memhook mh;

            // Populate the queue with the smaller reference vector
            for (size_t j = 0; j < n_smaller; j++) {
                q4.push(gt_3[j]);
            }

            // Ensure the queue was properly setup
            ASSERT_EQ(gt_3.size(), q4.size());
            ASSERT_EQ(n_smaller, mh.n_allocs());
        }

        // Queues of different sizes should always be false
        {
            Memhook mh;
            ASSERT_EQ(false, q1 == q4);
            ASSERT_EQ(false, q4 == q3);
            // Check that comparison does not allocate extra memory
            ASSERT_EQ(0ULL, mh.n_allocs());
        }
    }
    
    // Make sure that almost equal queues aren't equal
    for (size_t i = 0; i < TEST_ITER; i++) {
        // Generate a reference vector
        const size_t n = t.range(10ULL, 0x999ULL);
        std::vector<int> gt_1(n);
        t.fill(gt_1.begin(), gt_1.end());

        // Checking two almost equivalent queues
        Queue<int> q1;
        Queue<int> q2;

        // Random index for difference
        const size_t diff_idx = t.range<size_t>(1ULL, n);

        // Populate the queues with the reference vector data
        for (size_t j = 0; j < n; j++) {
            q1.push(gt_1[j]);

            if (j != diff_idx) {
                q2.push(gt_1[j]);
            } else {
                const int x = gt_1[j] + 1;
                q2.push(x);
            }
        }

        // The queues should not be equivalent if 1 element is different
        {
            Memhook mh;
            ASSERT_EQ(false, q1 == q2);
            // Check that comparison does not allocate extra memory
            ASSERT_EQ(0ULL, mh.n_allocs());
        }
    }
}
