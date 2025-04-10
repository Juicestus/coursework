#include "executable.h"
#include <vector>
#include <cmath>
#include "box.h"

size_t vec_alloc_upperbound(size_t sz) {
    return std::ceil(std::log2(sz)) + 1;
}

template<class T, size_t reservation = 0ULL>
class reserved_vector : public std::vector<T> {
    
    public:

    reserved_vector() { this->reserve(reservation); }
};

constexpr size_t MAX_SIZE = 0xFF;

TEST(push_move_and_efficient) {

    using box = Box<int>;
    using PQ = PriorityQueue<box, reserved_vector<box, MAX_SIZE>>;
    Typegen t;

    for(size_t k = 0; k < TEST_ITER; k++) {

        size_t n = t.range<size_t>(MAX_SIZE);

        std::vector<box> boxes(n);
        for(size_t i = 0; i < n; i++)
            boxes[i] = Box<int>(t.get<int>());

        PQ pq;
        
        {
            Memhook mh;

            {
                for(size_t i = 0; i < n; i++)
                    pq.push(std::move(boxes[i]));
            }

            ASSERT_LE(mh.n_allocs(), 0ULL);
        }

        {
            Memhook mh;

            {
                for(size_t i = 0; i < n; i++)
                    pq.pop();
            }

            ASSERT_EQ(0ull, mh.n_allocs());
        }
        
    }

}