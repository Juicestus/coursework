#include "executable.h"
#include "Queue.h"
#include "box.h"

#include <vector>

TEST(queue_push_move_and_back) {
    Typegen t;

    for (size_t i = 0; i < TEST_ITER; i++) {

        // Generate a reference vector
        const size_t n = t.range(0x999ULL);
        std::vector<int> gt(n);
        t.fill(gt.begin(), gt.end());

        {
            // Uses modified new to catch uninitialized memory
            Queue<Box<int>>* q = new Queue<Box<int>>();;
            
            // Convert reference vector to Box types
            std::vector<Box<int>> boxes(n);
            for (size_t i = 0; i < n; i++) {
                boxes[i] = gt[i];
            }

            Memhook mh;

            for (size_t i = 0; i < n; i++) {
                // Uses push move
                q->push(std::move(boxes[i]));
                ASSERT_EQ(gt[i], *q->back());
            }

            // Ensure nodes have been allocated
            // Allocations shouldn't occur for other memory
            ASSERT_EQ(n, mh.n_allocs());
            ASSERT_EQ(n, q->size());

            delete q;

            // Allocated memory should be freed
            ASSERT_EQ(n, mh.n_scoped_frees());
            ASSERT_EQ(2 * n + 1, mh.n_frees());

        }
        
    }
}