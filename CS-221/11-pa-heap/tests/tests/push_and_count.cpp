#include "executable.h"
#include <cmath>

size_t full_levels(size_t n)  {
    return std::floor(std::log2(n + 1));
}

struct comparison_tracking_comparitor {
    static size_t comparisons;
    
    bool operator()(int const & l, int const & r) const {
        comparisons++;
        return l < r;
    }
};

size_t comparison_tracking_comparitor::comparisons = 0;

TEST(push_and_count) {
    Typegen t;
    
    for(size_t i = 0; i < TEST_ITER; i++) {
        size_t n = t.range<size_t>(0xFFF);

        std::vector<int> monotonic_increase(n);
        std::vector<int> monotonic_decrease(n);
        std::vector<int> random(n);

        t.fill(monotonic_increase.begin(), monotonic_increase.end());
        t.fill(monotonic_decrease.begin(), monotonic_decrease.end());
        t.fill(random.begin(), random.end());

        std::sort(monotonic_increase.begin(), monotonic_increase.end());
        std::sort(monotonic_decrease.rbegin(), monotonic_decrease.rend());

        size_t & comparisons = comparison_tracking_comparitor::comparisons;

        // Push values less than all prior values
        // No swaps should occur
        {
            PriorityQueue<int, std::vector<int>, comparison_tracking_comparitor> pq;

            for(size_t i = 0; i < n; i++) {
                comparisons = 0ULL;

                pq.push(monotonic_decrease[i]);

                ASSERT_EQ((pq.size() > 1 ? 1ull : 0ull), comparisons);
                ASSERT_EQ(i + 1, pq.size()); // plus 1 is to include item inserted this iteration
            }
        }

        // Push values guaranteed to perform a full downheap
        // Ensure all parents are swapped
        {
            PriorityQueue<int, std::vector<int>, comparison_tracking_comparitor> pq;

            for(size_t i = 0; i < n; i++) {
                size_t l = full_levels(pq.size());

                comparisons = 0ULL;

                pq.push(monotonic_increase[i]);

                ASSERT_EQ(l, comparisons);
                ASSERT_EQ(i + 1, pq.size());
            }
        }

        // Upperbound should hold for downheap on random data
        {
            PriorityQueue<int, std::vector<int>, comparison_tracking_comparitor> pq;

            for(size_t i = 0; i < n; i++) {
                size_t l = full_levels(pq.size());

                comparisons = 0ULL;

                pq.push(random[i]);

                ASSERT_LE(comparisons, l);
                ASSERT_EQ(i + 1, pq.size());
            }
        }

    }
}