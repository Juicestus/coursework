#pragma once

#include <filesystem>
#include <fstream>
#include <algorithm>
#include <list>
#include <vector>

#include "weighted-graph.hpp"
#include "graph-algorithms.h"

namespace fs = std::filesystem;

using uint = unsigned int;

fs::path get_graph_path();

std::vector<fs::path> get_graphs(fs::path const & graphs, std::string const & type);

WeightedGraph<uint> read_graph(fs::path const & graph_path);

template <typename T>
struct shortest_path {
    T initial_node;
    T destination_node;
    std::vector<std::list<T>> paths;

    bool contains_shortest_path(std::list<T> const & path) const {
        return
            std::any_of(paths.begin(), paths.end(), [path](std::list<T> const & l) {
                return std::equal(l.begin(), l.end(), path.begin(), path.end());
            });
    }
};

template <typename T>
std::istream & operator>>(std::istream & i, struct shortest_path<T> & path) {
    std::string line;
    
    if(!std::getline(i, line))
        return i;
    
    std::size_t spx = line.find_first_of(':');

    if(spx == std::string::npos) {
        i.setstate(std::ios_base::failbit);
        return i;
    }

    std::stringstream src_dst { line.substr(0, spx) };
    std::stringstream paths { line.substr(spx + 1) };

    if(!(src_dst >> path.initial_node >> path.destination_node))
        return i;

    path.paths.clear();

    std::string paths_str;
    while(!paths.eof()) {
        std::getline(paths, paths_str, ',');

        if(paths.fail()) {
            i.setstate(paths.rdstate() | i.rdstate());
            return i;
        }

        std::stringstream path_ss { paths_str };
        
        std::list<T> path_list;

        T label;
        while(path_ss >> label) {
            path_list.push_back(label);
        }

        path.paths.push_back(std::move(path_list));
    }

    return i;
}

template<typename T> 
using shortest_path_pairs = std::vector<struct shortest_path<T>>;

template<typename T>
shortest_path_pairs<T> read_paths(fs::path const & graph_path) {
    fs::path shortest_pathfile = graph_path;
    shortest_pathfile /= graph_path.filename();
    shortest_pathfile += "_shortest_paths.dat";

    std::ifstream fs { shortest_pathfile };
    shortest_path_pairs<T> paths;
    shortest_path<T> path { };
    while(fs >> path)
        paths.push_back(std::move(path));
    
    return paths;
}