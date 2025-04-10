#include "executable.h"
#include <queue>
#include <algorithm>

TEST(push_pop_and_top) {
    Typegen t;

    std::priority_queue<double, std::vector<double>, std::greater<double>> gt_pq;
    PriorityQueue<double, std::vector<double>, std::greater<double>> pq;

    for(size_t k = 0; k < TEST_ITER; k++) {
        size_t n_push = t.range<size_t>(0xFFFull);
        size_t n_pop = t.range<size_t>(0x7FFull);
        
        for(size_t i = 0; i < n_push; i++) {
            double el = t.get<double>();

            gt_pq.push(el);
            pq.push(el);

            ASSERT_EQ(gt_pq.size(), pq.size());
            ASSERT_EQ(gt_pq.top(), pq.top());
        }

        n_pop = std::min(n_pop, gt_pq.size());

        for(size_t i = 0; i < n_pop; i++) {
            ASSERT_EQ(gt_pq.top(), pq.top());

            gt_pq.pop();
            pq.pop();

            ASSERT_EQ(gt_pq.size(), pq.size());
        }
    }
}
