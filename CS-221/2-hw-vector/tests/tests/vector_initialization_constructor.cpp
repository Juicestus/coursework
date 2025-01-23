#include "executable.h"

TEST(initialization_constructor) {
    Typegen t;
    
    for(size_t i = 0; i < 100; i++) {
        size_t count = t.range<size_t>(0xFFFF);
        Memhook m;

        {
            unsigned int el = t.range<unsigned int>(0xFFFF);
            Vector<unsigned int> vec(count, el);

            ASSERT_EQ(1UL, m.n_allocs());
            ASSERT_EQ(0UL, m.n_frees());
            ASSERT_EQ(count * sizeof(unsigned int), m.last_alloc().size);

            for(size_t i = 0; i < count; i++) {
                ASSERT_EQ(el, vec[i]);
            }
        }

        ASSERT_EQ(1UL, m.n_frees());

        {
            double el = t.unit<double>();
            Vector<double> vec(count, el);

            ASSERT_EQ(2UL, m.n_allocs());
            ASSERT_EQ(1UL, m.n_frees());
            ASSERT_EQ(count * sizeof(double), m.last_alloc().size);

            ASSERT_EQ(count, vec.size());
            ASSERT_EQ(count, vec.capacity());

            for(size_t i = 0; i < count; i++) {
                ASSERT_EQ(vec[i], el);
            }
        }

        ASSERT_EQ(2UL, m.n_frees());
    }
}