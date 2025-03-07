#include "generate_tree_data.h"
#include "executable.h"

TEST(insert_and_find) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {
        int lower = t.range(0, 250);
        int upper = lower + t.range(1, 250);

        depth_list<int> dlist = generate_tree_data(t, lower, upper);

        Memhook mh;

        {
            BinarySearchTree<int, int, comparison_tracking_comparator> tree;
            size_t & comparisons = comparison_tracking_comparator::comparisons;
            size_t expected_sz = 0;
            for(auto & [key, depth] : dlist) {
                int d = t.range(1, 10);

                std::pair<int, int> p { key, d * key };
                {
                    Memhook mh;
                    // Avoid calling move operator
                    tree.insert(p);
                    ASSERT_EQ(1ULL, mh.n_allocs());
                }

                comparisons = 0;

                {
                    Memhook mh;
                    ASSERT_VALUE_IN_TREE(d * key, tree, key);

                    // Depth (starting at zero) is bounded by:
                    //
                    // 2 * (d + 1) >= comparisons > d
                    //
                    // The lowerbound is established because one comparison
                    // must be made with the nodes on a path to the target
                    // node at depth d.
                    //
                    // The logic for the upperbound is similar but every node
                    // may result in two comparisons (in the worst case.)
                    if (depth) {
                        ASSERT_GT(comparisons, depth);
                        ASSERT_LE(comparisons, 2 * (depth + 1));
                    }

                    ASSERT_EQ(0ULL, mh.n_allocs());
                    ASSERT_EQ(0ULL, mh.n_frees());
                }

                ASSERT_EQ(++expected_sz, tree.size());
            }
        }
        ASSERT_EQ(mh.n_allocs(), mh.n_frees());
    }
}
