#include "generate_tree_data.h"
#include "executable.h"
#include <unordered_map>
#include <optional>
#include <cstring>
#include <cmath>

template<typename K, typename V>
using opt_pair = std::optional<std::pair<K, V>>;

template<typename K, typename V>
std::istream & operator>>(std::istream & s, opt_pair<K, V> & p) {
    char c;
    char buf[5];
    static char const TOK_NULL[] = "null";
    std::string deparams;
    std::stringstream ss;
    std::pair<K, V> pair;

    if(!(s >> c))
        return s;
    
    if(c == TOK_NULL[0]) {

        s.putback(TOK_NULL[0]);
        if(s.get(buf, sizeof(buf), ' ') && strcmp(buf, TOK_NULL) == 0) {
            p = std::nullopt;
            return s;
        }

        goto err;
    
    } else if(c != '(') {
        goto err;
    }

    if(!std::getline(s, deparams, ')'))
        return s;

    ss.str(std::move(deparams));

    if(!std::getline(ss, deparams, ','))
        return s;

    if(!(ss >> pair.second))
        goto err;

    ss.clear();
    ss.str(std::move(deparams));

    if(!(ss >> pair.first))
        goto err;

    p = pair;
    
    return s;

    err:
    s.setstate(std::ios::badbit);
    return s;
}


std::vector<opt_pair<int, int>> read_pair_heap(std::istream & is) {
    std::vector<opt_pair<int, int>> pairs;

    opt_pair<int, int> pair;
    while(is >> pair)
        pairs.push_back(pair);
    
    is.clear();
    
    return pairs;
}

inline ssize_t parent(ssize_t i) { return (i - 1) / 2; }
inline size_t left_child(ssize_t i) { return 2 * i + 1; }
inline size_t right_child(ssize_t i) { return 2 * i + 2; }
inline bool    is_root(ssize_t i) { return i == 0; }
inline bool    is_left_child(size_t i) { return i % 2 == 1; }

void maybe_print_dbg(BinarySearchTree<int, int> const & tree) {
    if(TREE_ASSERT_PRINT_SZ_LIMIT > tree.size()) {
        tdbg << "----- [begin levelByLevel] -----" << std::endl;
        printLevelByLevel(tree, tdbg);
        tdbg << "----- [end levelByLevel] -----" << std::endl;
    }

    maybe_print_tree(tdbg, tree);
}

TEST(print_level_by_level) {
    Typegen t;

    for(size_t i = 0; i < TEST_ITER; i++) {
        size_t sz = i == 0 ? 0ULL : t.range<size_t>(1, 64);
        
        std::stringstream ss;

        depth_list<int> dlist = generate_tree_data<int>(t, 0ULL, sz);
        std::unordered_map<int, int> value_map;

        for(auto const & [key, _] : dlist)
            value_map[key] = t.get<int>();

        BinarySearchTree<int, int> bst;

        for(auto const & [key, depth] : dlist)
            bst.insert({key, value_map[key]});

        printLevelByLevel(bst, ss);
        
        std::vector<opt_pair<int, int>> pairs = read_pair_heap(ss);

        std::vector<value_depth_pair<int>> vec(sz);
        std::copy(dlist.begin(), dlist.end(), vec.begin());

        std::sort(vec.begin(), vec.end(), 
            [&](value_depth_pair<int> const & l, value_depth_pair<int> const & r) { 
               if(l.depth == r.depth)
                    return l.key < r.key;
                
                return l.depth < r.depth;
            }
        );

        size_t expected_sz = vec.empty() ? 0ULL : (pow(2, vec.back().depth + 1) - 1);

        tdbg << "Expected 2^(d + 1) - 1 nodes in tree. Got " << pairs.size() << "." << std::endl;
        maybe_print_dbg(bst);
        ASSERT_EQ(expected_sz, pairs.size());
        
        auto it = vec.cbegin();
        
        for(auto & pair : pairs) {
            if(pair) {
                tdbg << "Key " << it->key << " does not match expected key " << pair->first << "." << std::endl;
                maybe_print_dbg(bst);
                ASSERT_EQ(it->key, pair->first);
                ASSERT_EQ(value_map[it->key], pair->second);
                it++;
            }
        }
        
        for(size_t i = 0; i < vec.size(); i++) {
            auto const & pair = pairs[i];
            
            if(pair) {
                if(!is_root(i)) {
                    size_t pidx = parent(i);

                    if(is_left_child(i)) {
                        tdbg << "key(parent) < key(child)" << std::endl;
                        maybe_print_dbg(bst);
                        ASSERT_GT(pairs[pidx]->first, pair->first);
                    } else {
                        tdbg << "key(parent) > key(child)" << std::endl;
                        maybe_print_dbg(bst);
                        ASSERT_LT(pairs[pidx]->first, pair->first);
                    }
                }

                if(pairs.size() > left_child(i)) {
                    auto const & left = pairs[left_child(i)];
                    auto const & right = pairs[right_child(i)];
                    
                    if(left) {
                        tdbg << "Misordering of keys [key(left_child) > key(parent)]" << std::endl;
                        maybe_print_dbg(bst);
                        ASSERT_LT(left->first, pair->first);
                    }
                    
                    if(right) {
                        tdbg << "Misordering of keys [key(right_child) < key(parent)]" << std::endl;
                        maybe_print_dbg(bst);
                        ASSERT_GT(right->first, pair->first);
                    }
                }
            } else {
                if(pairs.size() > left_child(i)) {
                    auto const & left = pairs[left_child(i)];
                    auto const & right = pairs[right_child(i)];
                    
                    tdbg << "Children of null nodes should be null" << std::endl;
                    maybe_print_dbg(bst);
                    ASSERT_FALSE(left || right);
                }
            }
        }
    }
}