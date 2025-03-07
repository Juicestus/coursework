#pragma once

#ifndef TREE_ASSERT_PRINT_SZ_LIMIT
#define TREE_ASSERT_PRINT_SZ_LIMIT 15
#endif

template<typename K, typename V, typename C>
std::ostream & maybe_print_tree(std::ostream & o, BinarySearchTree<K, V, C> const & tree) {
    #if defined(TREE_ASSERT_VIZ) || defined(TREE_ASSERT_PRINT)
    size_t sz = tree.size();
    if(sz <= TREE_ASSERT_PRINT_SZ_LIMIT) {
        o << "-----[begin tree]-----" << std::endl;
        #ifdef TREE_ASSERT_VIZ
        vizTree(tree, o);
        #else
        #ifdef TREE_ASSERT_PRINT
        printTree(tree, o);
        #endif
        #endif
        o << "-----[end tree]-----" << std::endl;
    } else {
        o << "Tree printout omitted _size = " << sz << " < TREE_ASSERT_PRINT_SZ_LIMIT [" << TREE_ASSERT_PRINT_SZ_LIMIT << "]" << std::endl;
    }
    #endif
    return o;
}

template<typename K, typename V, typename C>
std::ostream & _assert_value_exists_in_tree(
    std::ostream & o, 
    V const & expected_value, 
    BinarySearchTree<K, V, C> const & tree, 
    K const & key
) {
    const V & value = tree.find(key);
    
    if(value != expected_value) {
        o << "Expected (" << key << ", " << expected_value 
        << ") to exists in the tree. Lookup for \"" << key << "\" instead resulted in \"" 
        << value << "\"." << std::endl;
        
        maybe_print_tree(o, tree);

        return o;
    }

    return o;
}

#define ASSERT_VALUE_IN_TREE(expected_value, tree, key) \
    MK_ASSERT(_assert_value_exists_in_tree, expected_value, tree, key)

namespace {
    template<typename K, typename V>
    void report_kv_lookup_failure(std::ostream & o, V const & expected_value, K const & key, V const & value) {
        o << "Expected (" << key << ", " << expected_value 
        << ") to exists in the tree. Lookup for \"" << key << "\" instead resulted in \"" 
        << value << "\"." << std::endl;
    }
}


template<typename K, typename V, typename C>
std::ostream & _tree_pairs_contained_and_found(
    std::ostream & o, 
    std::vector<std::pair<K, V>> const & pairs, 
    BinarySearchTree<K, V, C> const & tree
) {
    
    for(auto const & [key, expected_value] : pairs) {
        if(!tree.contains(key)) {
            o << "Could not find " << key << " in tree." << std::endl;
            maybe_print_tree(o, tree);
            return o;
        }

        V const & value = tree.find(key);

        if(value != expected_value) {
            report_kv_lookup_failure(o, expected_value, key, value);
            maybe_print_tree(o, tree);
            return o;
        }
    }

    return o;
}

#define ASSERT_TREE_PAIRS_CONTAINED_AND_FOUND(pairs, tree) \
    MK_ASSERT(_tree_pairs_contained_and_found, pairs, tree)

struct comparison_tracking_comparator {
    static size_t comparisons;
    
    bool operator()(int const & l, int const & r) const {
        comparisons++;
        return l < r;
    }
};

size_t comparison_tracking_comparator::comparisons = 0;

template<typename K, typename V, typename C>
std::ostream & _assert_insertion_comparisons_between(
    std::ostream & o, 
    size_t lower_bound,
    size_t upper_bound,
    BinarySearchTree<K, V, C> & tree,
    typename BinarySearchTree<K, V>::pair const & pair 
    ) {
    size_t & comparisons = comparison_tracking_comparator::comparisons;
    comparisons = 0;
    
    tree.insert(pair);

    if(comparisons < lower_bound || comparisons > upper_bound) {
        o   << "Inserting (" << pair.first << ", " << pair.second << "). "
            << "Expected the number of comparisons made while traversing"
            << " the insertion path in the tree to be between " << lower_bound
            << " and " << upper_bound << "." << std::endl
            << "Instead insert resulted in " << comparisons << " comparisons." << std::endl;
        
        maybe_print_tree(o, tree);

        return o;
    }

    return o;  
}

#define INSERT_AND_ASSERT_COMPARISONS_BETWEEN(lower_bound, upper_bound, tree, pair) \
    MK_ASSERT(_assert_insertion_comparisons_between, lower_bound, upper_bound, tree, pair)
