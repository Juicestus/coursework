#include "executable.h"
#include <queue>

TEST(push_and_top) {
    Typegen t;

    std::priority_queue<double, std::vector<double>, std::greater<double>> gt_pq;
    PriorityQueue<double, std::vector<double>, std::greater<double>> pq;
    PriorityQueue<double, std::vector<double>, std::greater<double>> pq_moved;
    for(size_t k = 0; k < TEST_ITER; k++) {
        size_t n = t.range<size_t>(0xFFF);
        
        for(size_t i = 0; i < n; i++) {
            double el = t.get<double>();

            gt_pq.push(el);
            pq.push(el);
            pq_moved.push(std::move(el));

            ASSERT_EQ(gt_pq.size(), pq.size());
            ASSERT_EQ(gt_pq.top(), pq.top());
        }
    }
}