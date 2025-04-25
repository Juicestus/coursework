#pragma once

#include <optional>
#include <unordered_map>

#include "weighted-graph.hpp"
#include "graph-types.h"

// HINT when calling relax, you have to specify the template arugment.
// Therefore, relax(u, v, w, d, p) doesn't work.
// For example, you must say relax<int>(u, v, w, d, p).

template <typename T>
bool relax(value_type<T> u, value_type<T> v, weight_type<T> w,
std::unordered_map<value_type<T>, weight_type<T>>& distances,
std::unordered_map<value_type<T>, std::optional<value_type<T>>>& predecessors)
{
    // TODO relax the distance to v from u with weight w by changing the distances and predecessors maps as necessary
    // If the New Distance to v (Through u) is Shorter Than the Current Distance to v:
    if (distances[u] + w < distances[v])
    {
        // Update Distance to v and Predecessor of v Accordingly
        distances[v] = distances[u] + w;
        predecessors[v] = u;
        // Return True (Found Shorter Path)
        return true;
    }
    // Otherwise, Return False (Did Not Find Shorter Path)
    return false;
}

template <typename T>
weight_type<T> infinity() {
    return std::numeric_limits<weight_type<T>>::max();
}

template <typename T>
void initializeSingleSource(const WeightedGraph<T>& graph, vertex_type<T> initial_node,
std::unordered_map<value_type<T>, weight_type<T>>& distances,
std::unordered_map<value_type<T>, std::optional<value_type<T>>>& predecessors)
{
    for (auto it = graph.begin(); it != graph.end(); ++it) {
        const auto& vertex = it->first;
        distances[vertex] = infinity<T>();
        predecessors[vertex] = std::nullopt;
    }
    distances.at(initial_node) = 0;
}

template <typename T>
class DijkstraComparator {
    std::unordered_map<value_type<T>, weight_type<T>>& distances;
public:
    DijkstraComparator(std::unordered_map<value_type<T>, weight_type<T>>& distances) : distances{distances} {}
    bool operator()(const value_type<T>& a, const value_type<T>& b) {
        return distances.at(a) > distances.at(b);
    }
};

template <typename T>
void updateHeap(std::priority_queue<value_type<T>, std::vector<value_type<T>>, DijkstraComparator<T>>& q,
std::unordered_map<value_type<T>, weight_type<T>>& distances)
{
    std::make_heap(const_cast<value_type<T>*>(&q.top()),
            const_cast<value_type<T>*>(&q.top()) + q.size(),
            DijkstraComparator<T>{distances});
}
