#include "executable.h"
#include "box.h"

TEST(constructor_insert_copies) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        size_t sz = t.range<size_t>(100);

        // try a integral value, new initalization syntax
        // is a common error
        {
            Memhook mh;

            const int value = t.get<int>();

            List<int> * ll = new List<int>(sz, value);

            // Each node should be allocated individually
            ASSERT_EQ(sz + 1, mh.n_allocs());
            ASSERT_EQ(sz, ll->size());

            // All elements should be zero initalized
            auto it = ll->cbegin();
            for(; it != ll->cend(); it++)
                ASSERT_EQ(value, *it);

            // Pointers should be set in the reverse
            // direction
            while(it != ll->cbegin())
                ASSERT_EQ(value, *(--it));

            delete ll;

            // Let's not lose memory
            ASSERT_EQ(sz + 1, mh.n_frees());
        }

        {
            Memhook mh;

            const double value = t.unit<double>();

            List<Box<double>> * ll = new List<Box<double>>(sz, value);
            
            ASSERT_EQ(sz, ll->size());
            
            // Prevent additional, unneeded copies
            // Also ensure constructor is called
            ASSERT_EQ(2 * sz + 2, mh.n_allocs());

            for(auto it = ll->cbegin(); it != ll->cend(); it++) {
                ASSERT_EQ(value, **it);
            }

            delete ll;

            // Ensure memory is freed
            ASSERT_EQ(2 * sz + 2, mh.n_frees());
        }
    }
}
