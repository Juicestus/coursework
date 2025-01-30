#include "executable.h"
#include <vector>

TEST(move_constructor) {
    Typegen t;

	for(size_t sz = 0; sz < 0xFF; sz++) {
        Vector<int> original(sz);
        std::vector<int> gt(sz);

        for(size_t i = 0; i < sz; i++)
            original[i] = gt[i] = t.get<int>();
        
        size_t original_cap = original.capacity();

        {
            Memhook mh;

            Vector<int> move = std::move(original);

            ASSERT_EQ(original_cap, move.capacity());
            ASSERT_EQ(sz,           move.size());
            ASSERT_EQ(0UL,          mh.n_allocs());
            ASSERT_EQ(0UL,          mh.n_frees());

            for(size_t i = 0; i < sz; i++) {
                ASSERT_EQ(move[i], gt[i]);
            }

        }

        ASSERT_EQ(0UL, original.capacity());
        ASSERT_EQ(0UL, original.size());

        // Test reallocation to confirm original is empty 
        {
            Memhook mh;

            original.push_back(t.get<int>());

            ASSERT_EQ(1UL, mh.n_allocs());
            ASSERT_EQ(1UL * sizeof(int), mh.last_alloc().size);
        }
    }
}