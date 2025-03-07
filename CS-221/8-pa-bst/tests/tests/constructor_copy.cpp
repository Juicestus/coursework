#include "executable.h"
#include "generate_tree_data.h"
#include "EvilBox.h"

TEST(constructor_copy) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        size_t sz = i == 0 ? 0ULL : t.range<size_t>(1, 2048);

        auto pairs = generate_kv_pairs<int, int>(t, sz, true);

        BinarySearchTree<int, int> bst;

        for(auto const & pair : pairs)
            bst.insert(pair);

        size_t n_allocs, n_frees;

        Memhook mh;
        BinarySearchTree<int, int> bst_cpy { bst };
        n_allocs = mh.n_allocs();
        n_frees = mh.n_frees();

        tdbg << "Size mismatch" << std::endl;
        maybe_print_tree(tdbg, bst_cpy);
        ASSERT_EQ(sz, bst_cpy.size());

        tdbg << "Allocation mismatch" << std::endl;
        maybe_print_tree(tdbg, bst_cpy);
        ASSERT_EQ(sz, n_allocs);
        ASSERT_EQ(0ULL, n_frees);

        ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(pairs, bst_cpy);

        tdbg << "Size mismatch in source object" << std::endl;
        ASSERT_EQ(sz, bst.size());
        ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(pairs, bst);

        auto new_pairs1 = generate_kv_pairs<int, int>(t, sz);
        auto new_paris2 = generate_kv_pairs<int, int>(t, sz);

        for(auto const & pair : new_pairs1)
            bst.insert(pair);

        for(auto const & pair : new_paris2)
            bst_cpy.insert(pair);

        ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(new_pairs1, bst);
        ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(new_paris2, bst_cpy);
    }
}

TEST(constructor_copy_evilbox) {
    Typegen t;
    for(size_t i = 0; i < EVILBOX_TEST_ITER; i++) {
        using tree_t = BinarySearchTree<EvilBox<int>, int, EvilBox<int>::Comparator<std::less<int>>>;
        size_t sz = i == 0 ? 0ULL : t.range<size_t>(1, 2048);

        auto pairs = map_pairs<int, int, EvilBox<int>, int>(generate_kv_pairs<int, int>(t, sz, true));

        tree_t bst;

        for(auto const & pair : pairs)
            bst.insert(pair);

        size_t n_allocs, n_frees;

        Memhook mh;
        tree_t bst_cpy { bst };
        n_allocs = mh.n_allocs();
        n_frees = mh.n_frees();

        tdbg << "Size mismatch" << std::endl;
        maybe_print_tree(tdbg, bst_cpy);
        ASSERT_EQ(sz, bst_cpy.size());

        tdbg << "Allocation mismatch" << std::endl;
        maybe_print_tree(tdbg, bst_cpy);
        ASSERT_EQ(sz*2, n_allocs);
        ASSERT_EQ(0ULL, n_frees);

        ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(pairs, bst_cpy);

        tdbg << "Size mismatch in source object" << std::endl;
        ASSERT_EQ(sz, bst.size());
        ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(pairs, bst);

        auto new_pairs1 = map_pairs<int, int, EvilBox<int>, int>(generate_kv_pairs<int, int>(t, sz));
        auto new_paris2 = map_pairs<int, int, EvilBox<int>, int>(generate_kv_pairs<int, int>(t, sz));

        for(auto const & pair : new_pairs1)
            bst.insert(pair);

        for(auto const & pair : new_paris2)
            bst_cpy.insert(pair);

        ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(new_pairs1, bst);
        ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(new_paris2, bst_cpy);
    }
}
