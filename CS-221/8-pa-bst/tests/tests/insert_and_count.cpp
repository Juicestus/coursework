#include "generate_tree_data.h"
#include "executable.h"
#include "EvilBox.h"

TEST(insert_and_count) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {
        int lower = t.range(0, 250);
        int upper = lower + t.range(1, 250);

        depth_list<int> dlist = generate_tree_data(t, lower, upper);

        Memhook mh;
        {
            BinarySearchTree<int, int, comparison_tracking_comparator> tree;
            size_t expected_sz = 0;
            for(const auto & [key, depth] : dlist) {

                int odd_value = 2 * key + 1;
                int even_value = 2 * key;

                size_t comparisons;

                {
                    Memhook mh;

                    INSERT_AND_ASSERT_COMPARISONS_BETWEEN(
                        depth, 2 * depth, 
                        tree, (std::pair { key, even_value })
                    );

                    comparisons = comparison_tracking_comparator::comparisons;

                    ASSERT_EQ(1ULL, mh.n_allocs());
                }

                {
                    Memhook mh;

                    INSERT_AND_ASSERT_COMPARISONS_BETWEEN(
                        comparisons, comparisons + 2,
                        tree, (std::pair { key, odd_value })
                    );

                    // Should not allocate new memory
                    // Place in old location
                    ASSERT_EQ(0ULL, mh.n_allocs());
                    ASSERT_EQ(0ULL, mh.n_frees());
                }

                ASSERT_EQ(++expected_sz, tree.size());
            }
        }
        ASSERT_EQ(mh.n_allocs(), mh.n_frees());
    }
}
