#pragma once

#include "weighted-graph.hpp"

// value represented by nodes in the graph
template <typename T>
using value_type = typename WeightedGraph<T>::value_type;
// edge weight type
template <typename T>
using weight_type = typename WeightedGraph<T>::weight_type;

// vertex type (same as const value_type)
template <typename T>
using vertex_type = typename WeightedGraph<T>::vertex_type;
// edge type (mostly unused)
template <typename T>
using edge_type = typename WeightedGraph<T>::edge_type;
// type for adjacency list of edges
template <typename T>
using adjacency_list = typename WeightedGraph<T>::adjacency_list;

// size type for weighted graph is the size type for its container
template <typename T>
using size_type = typename WeightedGraph<T>::size_type;

// uses container iterators for outer iterator
template <typename T>
using iterator = typename WeightedGraph<T>::iterator;
// uses container const iterators for outer const iterator
template <typename T>
using const_iterator = typename WeightedGraph<T>::const_iterator;

// uses adjacency list iterators for inner iterator
template <typename T>
using edge_iterator = typename WeightedGraph<T>::edge_iterator;
// uses adjacency list const iterators for inner const iterator
template <typename T>
using const_edge_iterator = typename WeightedGraph<T>::const_edge_iterator;