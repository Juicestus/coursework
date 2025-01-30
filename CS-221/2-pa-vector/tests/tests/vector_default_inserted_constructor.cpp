#include "executable.h"
#include <string>

TEST(default_inserted_constructor) {
    Typegen t;
    
    for(size_t i = 0; i < 100; i++) {
        size_t count = t.range<size_t>(0xFFFF);
        Memhook m;

        {
            Vector<int> vec(count);

            ASSERT_EQ(count, vec.size());
            ASSERT_EQ(1UL, m.n_allocs());
            ASSERT_EQ(0UL, m.n_frees());
            ASSERT_EQ(count * sizeof(int), m.last_alloc().size);

            for(size_t i = 0; i < vec.size(); i++) {
                ASSERT_EQ(0, vec[i]);
            }
        }

        {
            Vector<double *> vec(count);

            ASSERT_EQ(count, vec.size());
            ASSERT_EQ(2UL, m.n_allocs());
            ASSERT_EQ(1UL, m.n_frees());
            ASSERT_EQ(count * sizeof(double *), m.last_alloc().size);

            for(size_t i = 0; i < vec.size(); i++) {
                ASSERT_EQ(nullptr, vec[i]);
            }
        }

        ASSERT_EQ(2UL, m.n_frees());

        {
            Vector<std::string> vec(count);

            ASSERT_EQ(count, vec.size());

            for(size_t i = 0; i < vec.size(); i++) {
                ASSERT_TRUE_(vec[i] == std::string(), "Make sure to use the default constructor for the type");
            }
        }
    }
}