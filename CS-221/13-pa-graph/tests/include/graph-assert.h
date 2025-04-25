#pragma once
#include <ostream>
#include <list>
#include <vector>

template<typename T>
std::ostream & print_path(std::ostream & o, std::list<T> const & l) {
    
    if(l.cbegin() == l.cend()) {
        return o << "(empty path)";
    }

    auto it = l.cbegin();
    auto last = --l.cend();
    for(; it != last; it++)
        o << (*it) << ", ";

    return o << *last;
}

std::ostream & _assert_shortest_paths_match(std::ostream & o, std::string const & type);

std::ostream & _assert_top_sort_order(std::ostream & o, std::string const & type);

#define ASSERT_SHORTEST_PATHS_MATCH(graph_type) \
    MK_ASSERT(_assert_shortest_paths_match, graph_type)

#define ASSERT_TOPOLOGICAL_ORDERING(graph_type) \
    MK_ASSERT(_assert_top_sort_order, graph_type)

