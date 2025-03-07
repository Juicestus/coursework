#include "generate_tree_data.h"
#include "executable.h"
#include "EvilBox.h"


TEST(erase) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        size_t chunk_sz = t.range<size_t>(1, 64);
        size_t iter = t.range<size_t>(1, 64);

        auto pairs = generate_kv_pairs<int, int>(t, chunk_sz * iter, true);
        std::vector<std::pair<int, int>> working_pairs;

        BinarySearchTree<int, int, comparison_tracking_comparator> bst;

        for(size_t j = 0; j < iter; j++) {

            for(size_t c = 0; c < chunk_sz; c++) {
                auto const & pair = pairs[chunk_sz * j + c];
                bst.insert(pair);
                working_pairs.push_back(pair);
            }

            ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(working_pairs, bst);
            ASSERT_EQ(working_pairs.size(), bst.size());

            size_t n_erase = t.range<size_t>(chunk_sz);

            for(size_t k = 0; k < n_erase; k++) {

                if (!bst.size())
                    break;

                size_t idx = t.range(bst.size());

                size_t & comparisons = comparison_tracking_comparator::comparisons;

                comparisons = 0;

                {
                    Memhook mh;
                    bst.erase(working_pairs[idx].first);
                    ASSERT_EQ(1ULL, mh.n_frees());
                }

                // Use the comparator
                ASSERT_GT(comparisons, 0ULL);

                ASSERT_FALSE(bst.contains(working_pairs[idx].first));
                working_pairs.erase(working_pairs.begin() + idx);
            }

            ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(working_pairs, bst);
        }
    }
}

TEST(erase_evilbox) {
    Typegen t;
    using tree_t = BinarySearchTree<EvilBox<int>, int, EvilBox<int>::Comparator<comparison_tracking_comparator>>;
    for(size_t i = 0; i < EVILBOX_TEST_ITER; i++) {
        size_t chunk_sz = t.range<size_t>(1, 64);
        size_t iter = t.range<size_t>(1, 64);

        auto pairs = map_pairs<int, int, EvilBox<int>, int>(generate_kv_pairs<int, int>(t, chunk_sz * iter, true));
        std::vector<std::pair<EvilBox<int>, int>> working_pairs;

        tree_t bst;

        for(size_t j = 0; j < iter; j++) {

            for(size_t c = 0; c < chunk_sz; c++) {
                auto const & pair = pairs[chunk_sz * j + c];
                bst.insert(pair);
                working_pairs.push_back(pair);
            }

            ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(working_pairs, bst);
            ASSERT_EQ(working_pairs.size(), bst.size());

            size_t n_erase = t.range<size_t>(chunk_sz);

            for(size_t k = 0; k < n_erase; k++) {

                if (!bst.size())
                    break;

                size_t idx = t.range(bst.size());

                size_t & comparisons = comparison_tracking_comparator::comparisons;

                comparisons = 0;

                {
                    Memhook mh;
                    bst.erase(working_pairs[idx].first);
                    // this seems fragile. The problem is that EvilBox allocates on move.
                    ASSERT_EQ(2ULL + mh.n_allocs(), mh.n_frees());
                }

                // Use the comparator
                ASSERT_GT(comparisons, 0ULL);

                ASSERT_FALSE(bst.contains(working_pairs[idx].first));
                working_pairs.erase(working_pairs.begin() + idx);
            }

            ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(working_pairs, bst);
        }
    }
}
