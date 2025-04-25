#include "sample-graphs.h"

fs::path get_graph_path() {
    fs::path cwd = fs::current_path();
    fs::path cur { cwd };
    static fs::path const graphs_indicator = fs::path {"assignment-graph-algorithms"}
        / "tests"
        / "graphs";
    

    for(auto part = --cwd.end();  part != cwd.begin(); --part) {
        for(auto ind = --graphs_indicator.end(); ind != --graphs_indicator.begin(); --ind) {
            
            if(*part != *ind) {
                continue;
            }

            fs::path graphs_canidate { cur };
            auto fwd = ind;
            
            if(fwd != graphs_indicator.end())
                fwd++;
            
            for(; fwd != graphs_indicator.end();)
                graphs_canidate /= *(fwd++);

            if(fs::is_directory(graphs_canidate))
                return fs::canonical(graphs_canidate);
        }

        cur /= "..";
    }

    throw std::runtime_error("Failed to find graphs directory");
}

std::vector<fs::path> get_graphs(fs::path const & graphs, std::string const & type) {
    std::vector<fs::path> paths;
    
    for(auto & graph : fs::directory_iterator { graphs }) {
        if(!graph.is_directory()) {
            continue;
        }

        std::string filename { graph.path().filename() };

        std::string graph_type = filename.substr(0, filename.find_first_of('-'));

        if (graph_type == type) {
            paths.push_back(graph.path());
        }
    }

    return paths;
}

WeightedGraph<uint> read_graph(fs::path const & graph_path) {
    WeightedGraph<uint> graph;

    fs::path dat_path = graph_path;
    dat_path /= graph_path.filename();
    dat_path += ".dat";
    
    std::ifstream fs { dat_path };

    if(!(fs >> graph))
        throw std::runtime_error("Failed to read input file " + std::string { graph_path });
    
    return graph;
}