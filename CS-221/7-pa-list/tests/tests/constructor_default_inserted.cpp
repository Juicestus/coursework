#include "executable.h"
#include "box.h"

TEST(constructor_default_inserted) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        size_t sz = t.range<size_t>(100);

        // try a integral value, new initalization syntax
        // is a common error
        {
            Memhook mh;

            List<int> * ll = new List<int>(sz);

            // Each node should be allocated individually
            ASSERT_EQ(sz + 1, mh.n_allocs());
            ASSERT_EQ(sz, ll->size());

            // All elements should be zero initalized
            auto it = ll->cbegin();
            for(; it != ll->cend(); it++)
                ASSERT_EQ(0, *it);

            // Pointers should be set in the reverse
            // direction
            while(it != ll->cbegin())
                ASSERT_EQ(0, *(--it));

            delete ll;

            // Let's not lose memory
            ASSERT_EQ(sz + 1, mh.n_frees());
        }

        // A container which will allocate memory
        // when the default constructor is called
        struct Container {
            Box<int> box;
            Container() : box(4) {}
        };

        {
            Memhook mh;

            List<Container> * ll = new List<Container>(sz);

            ASSERT_EQ(sz, ll->size());
            
            // Prevent additional, unneeded copies
            // Also ensure default constructor is called
            ASSERT_EQ(2 * sz + 3, mh.n_allocs());

            for(auto it = ll->cbegin(); it != ll->cend(); it++) {
                ASSERT_EQ(4, *(*it).box);
            }

            delete ll;

            // Ensure memory is freed
            ASSERT_EQ(2 * sz + 3, mh.n_frees());
        }
    }
}
