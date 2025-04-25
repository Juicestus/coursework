#include "graph-assert.h"
#include "sample-graphs.h"

static void print_graph_info(std::ostream & o, fs::path graph_path) {
    o << "Graph: " << graph_path.filename() << std::endl;
    o << "Located at: " << graph_path << std::endl;
    o << std::endl;
}

std::ostream & _assert_shortest_paths_match(std::ostream & o, std::string const & type) {
    fs::path graph_path = get_graph_path();

    std::vector<fs::path> graph_paths = get_graphs(graph_path, type);

    for(auto const & graph_path : graph_paths) {
        WeightedGraph<uint> graph = read_graph(graph_path);
        shortest_path_pairs<uint> all_paths = read_paths<uint>(graph_path);
        for(auto const & path : all_paths) {
            std::list<uint> shortest_path = dijkstrasAlgorithm(graph, path.initial_node, path.destination_node);

            if(!path.contains_shortest_path(shortest_path)) {
                print_graph_info(o, graph_path);

                o << "Shortest path from initial node " 
                  << path.initial_node
                  << " to destination node " 
                  << path.destination_node << std::endl;
                o << std::endl;

                o << "Dijkstra's algorithm returned path: " << std::endl;
                print_path<uint>(o, shortest_path);
                o << std::endl;

                o << std::endl;

                o << "Shortest path(s) include: " << std::endl;

                for(auto const & path : path.paths) {
                    print_path<uint>(o, path) << std::endl;
                }
                
                return o;
            }
            
        }
    }

    return o;
}

std::ostream & _assert_top_sort_order(std::ostream & o, std::string const & type) {
    fs::path graph_path = get_graph_path();
    std::vector<fs::path> graph_paths = get_graphs(graph_path, type);
    
    for(auto const & graph_path : graph_paths) {
        WeightedGraph<uint> graph = read_graph(graph_path);
        std::unordered_set<uint> visited;
        std::list<uint> sorted_graph = topologicalSort(graph);
        
        if(sorted_graph.size() != graph.size()) {
            print_graph_info(o, graph_path);

            o << "Number of vertices in graph and topological sort order do not match." << std::endl;
            o << "Expected: " << graph.size() << std::endl;
            o << "Actual: " << sorted_graph.size() << std::endl;

            o << "Returned topological sort ordering:" << std::endl;
            print_path<uint>(o, sorted_graph);
            
            return o;
        }

        for(auto vertex : sorted_graph) {
            visited.insert(vertex);
            for(auto const & [adj_vert, adj_weight]: graph.at(vertex)) {
                (void) adj_weight;
                
                if(visited.end() != visited.find(adj_vert)) {
                    print_graph_info(o, graph_path);

                    o << "Vertex: " << adj_vert;
                    o << " was found in adjacency list of vertex " << vertex << ". ";
                    o << vertex << " should appear before " << adj_vert << " in the topological ordering." << std::endl << std::endl;
                    
                    o << "Returned topological sort ordering:" << std::endl;
                    print_path<uint>(o, sorted_graph);

                    return o;
                }
            }
        }
    }

    return o;
}