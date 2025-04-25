#pragma once

#include <istream>
#include <ostream>
#include <sstream>
#include <limits>
#include <list>
#include <queue>
#include <string>
#include <unordered_set>
#include <unordered_map>

#include "weighted-graph.hpp"

#include "graph-types.h"

// if the arrow is a box, change to the other line
#define ARROW_SEPARATOR " \u2192 "
// #define ARROW_SEPARATOR " -> "

#include "top-sort-helpers.h"

/**
 * @brief Returns a Topological Ordering of the Graph - https://en.wikipedia.org/wiki/Topological_sorting#Depth-first_search
 *
 * @tparam T type of data stored by a vertex
 * @param graph graph upon which to perform a topological ordering
 * @return std::list<value_type<T>> list of nodes in a topological order, or an empty list if no such ordering exists
 */
template <typename T>
std::list<value_type<T>> topologicalSort(const WeightedGraph<T>& graph)
{
    std::unordered_map<value_type<T>, int> indegrees;
    std::unordered_map<value_type<T>, int> topological_numbers;

    // Compute Indegree of All Vertices
    computeIndegrees(graph, indegrees);

    // Initialize Empty List (Stores Top Sort Ordering)
    std::list<value_type<T>> k{};
    // Initialize Empty Queue (Tracks Discovered Vertices)
    std::queue<value_type<T>> q{};

    // Add All Vertices with Indegree 0 to Queue
    size_t n_vertex = 0;
    for (auto itv = graph.begin(); itv != graph.end(); itv++)
    {
        vertex_type<T> v = itv->first;
        if (indegrees.find(v) == indegrees.end())
        {
            q.push(v);
        }
        n_vertex++;
    }

    // While Queue is Not Empty (i.e. Still Nodes to Process):
    while (!q.empty())
    {
        // Pop Front of Queue (u) and Add to End of List
        vertex_type<T> u = q.front();
        q.pop();
        k.push_back(u);

        // For Each Edge (u, v) in Adjacency List of u:
        for (auto ite = graph.begin(u); ite != graph.end(u); ite++)
        {
            vertex_type<T> v = ite->first;
            weight_type<T> w = ite->second;
            // Decrement Indegree of v
            indegrees[v]--;
            // Add v to Queue if Indegree Becomes 0
            if (indegrees[v] == 0)
            {
                q.push(v);
            }
        }
    }

    // If Some Vertices Were Not Added to Top Sort Ordering (List):
    if (k.size() != n_vertex)
    {
        // A Cycle Was Detected, Meaning There is No Valid Top Sort Ordering of the Graph (Only Valid for DAGs)
        // Because of This, Return an Empty List
        return std::list<value_type<T>>();
    }

    // Otherwise, Return the List (A Valid Top Sort Ordering)
    return k;
}

// contains initializeSingleSource, relax, & updateHeap as well as the DijkstraComaparator
#include "dijkstras-helpers.h"

/**
 * @brief Dijkstra's Algorithm - https://canvas.tamu.edu/courses/136654/files/35930572/preview Slide 16
 *
 * @tparam T type of data stored by a vertex
 * @param graph weighted, directed graph to find single-source shortest-path
 * @param initial_node source node in graph for shortest path
 * @param destination_node destination node in graph for shortest path
 * @return std::list<value_type<T>> list of nodes along shortest path including initial_node and destination_node, empty if no path exists
 */
template <typename T>
std::list<value_type<T>> dijkstrasAlgorithm(const WeightedGraph<T>& graph, vertex_type<T> initial_node, vertex_type<T> destination_node)
{
    // Initialize Empty Distances Map
    std::unordered_map<value_type<T>, weight_type<T>> distances;
    // Initialize Empty Predecessors Map
    std::unordered_map<value_type<T>, std::optional<value_type<T>>> predecessors;
    // Initialize Empty Set (Stores Finalized Vertices, Sometimes Referred to as the "Cloud")
    std::unordered_set<value_type<T>> s;
    // Initialize Empty Priority Queue (Tracks "Closest" Unfinalized Vertices)
    std::priority_queue<value_type<T>, std::vector<value_type<T>>, DijkstraComparator<T>> q(DijkstraComparator<T>{distances});

    // PART 1: Running Dijkstra's Algorithm
    // Initialize Distances and Predecessors (Hint: Look At Provided Helper Functions)
    initializeSingleSource(graph, initial_node, distances, predecessors);

    // Add All Vertices to Priority Queue
    for (auto itv = graph.begin(); itv != graph.end(); itv++)
    {
        vertex_type<T> v = itv->first;
        q.push(v);
    }

    // While Priority Queue is Not Empty (i.e. Still Vertices Not in Cloud)
    while (!q.empty())
    {
        // Pop Top of Priority Queue (u)
        vertex_type<T> u = q.top();
        q.pop();

        // If Distance to u is Infinity:
        if (distances[u] == infinity<T>())
        {
            // There Are No More Vertices Outside the Cloud That Are Reachable From the Starting Node
            // Break From Loop, Completing Dijkstra's
            break;
        }
        // Add u to Cloud
        s.insert(u);
        
        // For Each Edge (u, v, w) in Adjacency List of u:
        for (auto ite = graph.begin(u); ite != graph.end(u); ite++)
        {
            vertex_type<T> v = ite->first;
            weight_type<T> w = ite->second;

            // If v is Already in Cloud:
            if (s.find(v) != s.end())
            {
                // Vertex v Has Already Been Finalized, So There is Nothing to Update
                // Continue to Next Edge
                continue;
            }

            // If Relaxation of Edge (u, v, w) is Successful:
            if (relax<T>(u, v, w, distances, predecessors))
            {
                // Update Priority Queue (Hint: Look At Provided Helper Functions)
                updateHeap(q, distances);
            }
        }
    }
    // TODO create list by walking backwards through predecessors from the end
    std::list<value_type<T>> k{};
    for (value_type<T> u = destination_node; ; ) {
        k.push_front(u);
        if (u == initial_node) break;
        auto optu = predecessors[u];
        if (!optu.has_value()) return {};
        u = *optu;
    }
    return k;
}

template <typename T>
std::ostream &operator<<(std::ostream &o, const WeightedGraph<T> &graph)
{
    for (auto it = graph.begin(); it != graph.end(); ++it)
    {
        const vertex_type<T> &vertex = it->first;
        const adjacency_list<T> &list = it->second;
        o << vertex << ": ";
        for (auto iit = list.begin(); iit != list.end(); ++iit)
        {
            const vertex_type<T> &destination = iit->first;
            const weight_type<T> &weight = iit->second;
            o << destination << "(" << weight << ')';
            auto next_iter = iit;
            if (++next_iter != list.end())
            {
                o << ARROW_SEPARATOR;
            }
        }
        auto next_iter = it;
        if (++next_iter != graph.end())
        {
            o << "\n";
        }
    }
    return o;
}

template <typename T>
std::istream &readEdge(std::istream &i, value_type<T> &vertex, weight_type<T> &weight)
{
    std::string s_vertex, s_weight;
    std::getline(i, s_vertex, '(');
    std::getline(i, s_weight, ')');
    std::istringstream stream(s_vertex + " " + s_weight);
    stream >> vertex >> weight;
    if (stream.fail())
    {
        i.setf(stream.flags());
    }
    return i;
}

template <typename T>
std::istream &operator>>(std::istream &i, WeightedGraph<T> &graph)
{
    std::string line;
    while (std::getline(i, line))
    {
        if (line.empty())
            break;
        std::istringstream line_stream(line);
        value_type<T> vertex;
        std::string s_vertex;
        std::getline(line_stream, s_vertex, ':');
        std::istringstream stream_vertex(s_vertex);
        stream_vertex >> vertex;
        if (stream_vertex.fail())
        {
            i.setf(stream_vertex.flags());
            break;
        }
        graph.push_vertex(vertex);
        std::string separator;
        value_type<T> edge_end;
        weight_type<T> edge_weight;
        while (readEdge<T>(line_stream, edge_end, edge_weight))
        {
            line_stream >> separator;
            graph.push_edge(vertex, edge_end, edge_weight);
        }
    }

    if(i.eof() and i.fail())
        i.clear(std::ios::eofbit);
    
    return i;
}
