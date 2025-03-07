#include "executable.h"
#include "generate_tree_data.h"

TEST(operator_move) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        size_t sz_src = i == 0 ? 0ULL : t.range<size_t>(1, 2048);
        size_t sz_dst = t.range(1, 2048);

        auto src_pairs = generate_kv_pairs<int, int>(t, sz_src, true);
        auto dst_pairs = generate_kv_pairs<int, int>(t, sz_dst, true);

        BinarySearchTree<int, int> src;
        BinarySearchTree<int, int> dst;

        for(auto const & pair : src_pairs)
            src.insert(pair);

        for(auto const & pair : dst_pairs)
            dst.insert(pair);

        size_t n_allocs, n_frees;

        {
            Memhook mh;
            dst = std::move(src);
            n_allocs = mh.n_allocs();
            n_frees = mh.n_frees();
        }

        tdbg << "Size mismatch" << std::endl;
        maybe_print_tree(tdbg, dst);
        ASSERT_EQ(sz_src, dst.size());

        tdbg << "Allocation mismatch" << std::endl;
        maybe_print_tree(tdbg, dst);
        ASSERT_EQ(0ULL, n_allocs);
        ASSERT_EQ(sz_dst, n_frees);

        ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(src_pairs, dst);

        #ifdef _ALT_EMPTY_STATE
        ASSERT_EQ(0, src.size());
        for(auto const & pair : pairs) {
            tdbg << "Should not contain values from source object" << std::endl;
            ASSERT_FALSE_(src.contains(pair));
        }
        #endif

        size_t sz = t.range(1, 1024);

        auto new_dst_pairs = generate_kv_pairs<int, int>(t, sz);
        auto new_src_pairs = generate_kv_pairs<int, int>(t, sz);

        for(auto const & pair : new_dst_pairs)
            dst.insert(pair);

        for(auto const & pair : new_src_pairs)
            src.insert(pair);

        ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(new_src_pairs, src);
        ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(new_dst_pairs, dst);
    }
}


TEST(operator_move_self_move_protection) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        size_t sz = t.range(1, 2048);
        auto pairs = generate_kv_pairs<int, int>(t, sz, true);
        BinarySearchTree<int, int> bst;

        for(auto const & pair : pairs)
            bst.insert(pair);

        bst = std::move(bst);

        ASSERT_EQ(sz, bst.size());
        ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(pairs, bst);
    }
}
