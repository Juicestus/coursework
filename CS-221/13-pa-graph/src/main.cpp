#include <fstream>
#include <iostream>

#include "weighted-graph.hpp"
#include "graph-algorithms.h"

#define GRAPH_TEXT \
"1: 2(4) → 4(3) → 5(3)\n" \
"2: 3(3) → 4(3) → 7(6)\n" \
"3: 4(1)\n" \
"4: 6(6) → 7(8)\n" \
"5:\n" \
"6: 5(5)\n" \
"7: 6(6)"

#define GRAPH_TYPE int

template <typename T>
void getGraph(WeightedGraph<T>& graph, int argc, char* argv[]) {
    if (argc < 2) {
        std::istringstream(GRAPH_TEXT) >> graph;
    } else {
        std::ifstream(argv[1]) >> graph;
    }
}

template <typename T>
std::ostream& printVertexList(std::ostream& o, std::list<T> list, std::string label) {
    o << "Start " << label << ": ";
    for (const auto& e : list) {
        o << e;
        if (&e != &list.back()) {
            o << ARROW_SEPARATOR;
        }
    }
    return o << " :End " << label;
}

int main(int argc, char* argv[]) {
    WeightedGraph<GRAPH_TYPE> graph; // most input files
    // WeightedGraph<std::string> graph; // inputCourses.dat

    getGraph(graph, argc, argv);

    std::cout << graph << std::endl;

    std::unordered_map<value_type<GRAPH_TYPE>, int> indegrees;
    computeIndegrees(graph, indegrees);
    for (auto it = indegrees.begin(); it != indegrees.end(); it++)
    {
        std::cout << "indeg(" << it->first << ")=" << it->second << "\n";
    }

    typename WeightedGraph<GRAPH_TYPE>::value_type start, end;
    // std::cout << "Input Start Vertex Label for Dijkstra's: ";
    // std::cin >> start;
    // std::cout << "Input End Vertex Label for Dijkstra's: ";
    // std::cin >> end;
    start = 2;
    end = 5;

    std::list<typename WeightedGraph<GRAPH_TYPE>::value_type> shortest_path = dijkstrasAlgorithm(graph, start, end);
    printVertexList(std::cout, shortest_path, "Dijkstra's") << std::endl;

    // std::list<typename WeightedGraph<GRAPH_TYPE>::value_type> topological_sort = topologicalSort(graph);
    // printVertexList(std::cout, topological_sort, "Topological Sort") << std::endl;
}
