#include <list>
#include <vector>
#include "typegen.h"

template<typename T>
struct value_depth_pair {
    T key;
    std::size_t depth;
};

template<typename T>
using depth_list = std::list<value_depth_pair<T>>;

template<typename T>
void _generate_tree_data(Typegen & t, T a, T b, std::size_t depth, depth_list<T> & list) {
    if(a >= b) return;
    
    T value = t.range<T>(a, b);

    list.push_back(std::move(value_depth_pair<T> { value, depth }));

    if(t.get<bool>()) {
        _generate_tree_data(t, value + 1, b, depth + 1, list);
        _generate_tree_data(t, a, value, depth + 1, list);
    } else {
        _generate_tree_data(t, a, value, depth + 1, list);
        _generate_tree_data(t, value + 1, b, depth + 1, list);
    }
}

template<typename T>
depth_list<T> generate_tree_data(Typegen & t, T a, T b) {
    depth_list<T> tree_data;

    _generate_tree_data(t, a, b, 0, tree_data);

    return tree_data;
}


template<typename K, typename V>
std::vector<std::pair<K, V>> generate_kv_pairs(Typegen t, size_t sz, bool unique = false) {
    std::vector<K> gt_keys(sz);

    if(unique)
        t.fill_unique(gt_keys.begin(), gt_keys.end());
    else
        t.fill(gt_keys.begin(), gt_keys.end());


    std::vector<V> gt_values(sz);

    if(unique)
        t.fill_unique(gt_values.begin(), gt_values.end());
    else
        t.fill(gt_values.begin(), gt_values.end());

    std::vector<std::pair<K, V>> pairs(sz);

    auto k_i = gt_keys.begin();
    auto k_j = gt_values.begin();
    for(size_t i = 0; i < sz; i++) {
        pairs[i] = { *(k_i++), *(k_j++) };
    }

    return pairs;
}

template<typename K, typename V, typename Kt, typename Vt>
std::vector<std::pair<Kt, Vt>> map_pairs(std::vector<std::pair<K, V>> vec) {
    std::vector<std::pair<Kt, Vt>> out{vec.size()};
    for (size_t i = 0; i < vec.size(); ++i) {
        out[i] = {Kt{vec[i].first}, Vt{vec[i].second}};
    }
    return out;
}
