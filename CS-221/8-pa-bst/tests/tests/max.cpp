#include "executable.h"
#include "generate_tree_data.h"
#include <algorithm>
#include <limits>
#include "EvilBox.h"

TEST(max) {
    Typegen t;
    for(size_t i = 0; i < TEST_ITER; i++) {
        size_t sz = t.range<size_t>(0, 1024);

        auto pairs = generate_kv_pairs<double, double>(t, sz);

        Memhook mh;
        BinarySearchTree<double, double> bst;

        double max_value, max_key;
        max_value = max_key = std::numeric_limits<double>::min();

        for(auto const & [key, value] : pairs) {
            if(key > max_key) {
                max_key = key;
                max_value = value;
            }

            bst.insert({key, value});

            auto const & max = bst.max();
            {
                tdbg << "Expected max key " << max_key << " got " << max.first << std::endl;
                maybe_print_tree(tdbg, bst);
                ASSERT_EQ(max_key, max.first);
            }

            {
                tdbg << "Got max value = " << max_value << " got " << max.second << std::endl;
                maybe_print_tree(tdbg, bst);
                ASSERT_EQ(max_value, max.second);
            }
        }
    }
}

TEST(max_evilbox) {
    Typegen t;
    for(size_t i = 0; i < EVILBOX_TEST_ITER; i++) {
        size_t sz = t.range<size_t>(0, 1024);

        auto pairs = map_pairs<double, double, EvilBox<double>, double>(generate_kv_pairs<double, double>(t, sz));

        Memhook mh;
        BinarySearchTree<EvilBox<double>, double, EvilBox<double>::Comparator<>> bst;

        double max_value, max_key;
        max_value = max_key = std::numeric_limits<double>::min();

        for(auto const & [key, value] : pairs) {
            if(*key > max_key) {
                max_key = *key;
                max_value = value;
            }

            bst.insert({key, value});

            // we could disable comparisons here to make sure they aren't searching for it

            auto const & max = bst.max();
            {
                tdbg << "Expected max key " << max_key << " got " << max.first << std::endl;
                maybe_print_tree(tdbg, bst);
                ASSERT_EQ(max_key, *max.first);
            }

            {
                tdbg << "Got max value = " << max_value << " got " << max.second << std::endl;
                maybe_print_tree(tdbg, bst);
                ASSERT_EQ(max_value, max.second);
            }
        }
    }
}
