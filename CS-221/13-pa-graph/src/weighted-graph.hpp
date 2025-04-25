#pragma once

#include <unordered_map>
#include <unordered_set>
#include <stdexcept>
#include <utility>

// directed, weighted graph data structure, stores vertices of type T
template <typename T>
class WeightedGraph {
public:
    // value represented by nodes in the graph
    using value_type = T;
    // edge weight type
    using weight_type = int;

    // vertex type (same as const value_type)
    using vertex_type = const value_type;
    // edge type (mostly unused)
    using edge_type = std::pair<vertex_type, weight_type>;
    // type for adjacency list of edges
    using adjacency_list = std::unordered_map<value_type, weight_type>;

private:
    // contains vertices and associates them to their adjacency lists
    using container_type = std::unordered_map<value_type, adjacency_list>;

public:
    // size type for weighted graph is the size type for its container
    using size_type = typename container_type::size_type;
    
    // uses container iterators for outer iterator
    using iterator = typename container_type::iterator;
    // uses container const iterators for outer const iterator
    using const_iterator = typename container_type::const_iterator;

    // uses adjacency list iterators for inner iterator
    using edge_iterator = typename adjacency_list::iterator;
    // uses adjacency list const iterators for inner const iterator
    using const_edge_iterator = typename adjacency_list::const_iterator;

private:
    // the internal data structure which stores the vertices and adjacency lists
    container_type graph;

public:
    // constructs an empty graph
    WeightedGraph() = default;
    // deep copies graph other
    WeightedGraph(const WeightedGraph& other) = default;
    // moves graph other
    WeightedGraph(WeightedGraph&& other) = default;
    // copy assigns graph other
    WeightedGraph& operator=(const WeightedGraph& other) = default;
    // move assigns graph other
    WeightedGraph& operator=(WeightedGraph&& other) = default;

    // returns true if the graph is empty, false otherwise
    bool empty() const { return graph.empty(); }
    // returns true if the adjacency list at the vertex is empty, false otherwise
    bool empty(const vertex_type& vertex) const { return graph.at(vertex).empty(); }
    // returns the size of the graph
    size_type size() const { return graph.size(); }
    // returns the size of the adjacency list at the vertex
    size_type size(const vertex_type& vertex) const { return graph.at(vertex).size(); }

    // returns a const& to the adjacency list at the vertex
    const adjacency_list& at(const vertex_type& vertex) const { return graph.at(vertex); }
    
    // adds a vertex to the graph
    std::pair<iterator, bool> push_vertex(const vertex_type& vertex) { return graph.insert(std::make_pair(vertex, adjacency_list())); }

    // removes a vertex from the graph (completely)
    size_type pop_vertex(vertex_type& vertex) {
        size_type retval = graph.erase(vertex);
        for (auto& [v, list] : graph) {
            (void) v; // do not use the vertex label
            retval += list.erase(vertex);
        }
        return retval;
    }

    // adds an edge to the graph
    std::pair<edge_iterator, bool> push_edge(const vertex_type& source, const vertex_type& destination, const weight_type& weight) {
        return graph.at(source).insert(std::make_pair(destination, weight));
    }

    // removes an edge from the graph
    size_type pop_edge(const vertex_type& source, const vertex_type& destination) {
        return graph.at(source).erase(destination);
    }

    // create an iterator to the beginning over the vertices (with their adjacency lists)
    iterator begin() { return graph.begin(); }
    // create a const iterator to the beginning over the vertices (with their adjacency lists)
    const_iterator begin() const { return graph.begin(); }
    // create a const iterator to the beginning over the vertices (with their adjacency lists)
    const_iterator cbegin() const { return graph.cbegin(); }

    // create an iterator to the ending over the vertices (with their adjacency lists)
    iterator end() { return graph.end(); }
    // create a const iterator to the ending over the vertices (with their adjacency lists)
    const_iterator end() const { return graph.end(); }
    // create a const iterator to the ending over the vertices (with their adjacency lists)
    const_iterator cend() const { return graph.cend(); }

    // create an iterator to the beginning of the edges in an adjacency list
    edge_iterator begin(const vertex_type& vertex) { return graph.at(vertex).begin(); }
    // create a const iterator to the beginning of the edges in an adjacency list
    const_edge_iterator begin(const vertex_type& vertex) const { return graph.at(vertex).begin(); }
    // create a const iterator to the beginning of the edges in an adjacency list
    const_edge_iterator cbegin(const vertex_type& vertex) const { return graph.at(vertex).cbegin(); }

    // create an iterator to the ending of the edges in an adjacency list
    edge_iterator end(const vertex_type& vertex) { return graph.at(vertex).end(); }
    // create a const iterator to the ending of the edges in an adjacency list
    const_edge_iterator end(const vertex_type& vertex) const { return graph.at(vertex).end(); }
    // create a const iterator to the ending of the edges in an adjacency list
    const_edge_iterator cend(const vertex_type& vertex) const { return graph.at(vertex).cend(); }

    // clear all of the vertices and edges from the graph
    void clear() { graph.clear(); }
    // clear all of the edges from (NOT to) the given vertex in the graph
    void clear(const vertex_type& vertex) { graph.at(vertex).clear(); }

};