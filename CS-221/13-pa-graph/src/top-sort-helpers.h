#pragma once

#include <unordered_map>

#include "weighted-graph.hpp"
#include "graph-types.h"

template <typename T>
void computeIndegrees(const WeightedGraph<T>& graph, std::unordered_map<value_type<T>, int>& indegrees) {
    for (auto itv = graph.begin(); itv != graph.end(); itv++)
    {
        vertex_type<T> u = itv->first;
        for (auto ite = graph.begin(u); ite != graph.end(u); ite++) 
        {
            vertex_type<T> v = ite->first;
            weight_type<T> w = ite->second;

            indegrees[v]++;
        }

    }
}
