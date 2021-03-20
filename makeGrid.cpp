#include "GridWithRoughBoundaries.h"

#include <iostream>
#include <optional>
#include <cstdlib>
#include <random>
#include <fstream>
#include <ranges>

template<class T>
using delayed = std::optional<T>;


const std::string k_usage = "Usage: makeGrid <nodes per side> <num source nodes> <GRAPH in file> <SOURCE in file>\n";

struct edge_weights{
  static constexpr int k_max = 1000000;
  static constexpr int k_min = 1;
};


int main(int argc, char* argv[])
{

    if(argc!=5)
    {
        std::cerr<<k_usage;
        return EXIT_FAILURE;
    }

    int nodes_per_side = std::stoi(argv[1]);
    int num_source_nodes = std::stoi(argv[2]);
    std::string graph_in_fname{argv[3]};
    std::string source_in_fname{argv[4]};

    GridWithRoughBoundaries g{nodes_per_side};

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_int_distribution<int> edge_weight_distribution(edge_weights::k_min,edge_weights::k_max);

    {
        std::ofstream graph_in_file(graph_in_fname);
        graph_in_file << g.nodes_per_side()*g.nodes_per_side() << " " << g.num_edges() << std::endl;

        g.traverse_edges([&](Vertex s, Vertex t)
        {
          graph_in_file << g.label(s) << " " << g.label(t) << " " << edge_weight_distribution(rng) << std::endl;
        });
    }

    {
        std::ofstream source_in_file(source_in_fname);
        source_in_file << num_source_nodes << " " << g.nodes_per_side()*2 << std::endl;

        std::vector<unsigned int> indices(g.nodes_per_side()*g.nodes_per_side());
        std::iota(indices.begin(), indices.end(), 0);
        std::shuffle(indices.begin(), indices.end(), std::mt19937(std::random_device()()));


        auto is_boundary = [&g](const Vertex& v) -> bool
        {
            return v.row ==0 and v.row == g.nodes_per_side()-1;
        };

        for (int i = 0; i<num_source_nodes; ++i)
        {
            while(is_boundary(g.vertex_from_label(indices[i]))) i++;
            source_in_file << indices[i] << std::endl;
        }

        for (int i = 0; i<g.nodes_per_side(); ++i)
        {
            source_in_file << g.label(Vertex{0,i}) << std::endl;
            source_in_file << g.label(Vertex{g.nodes_per_side()-1,i}) << std::endl;
        }

    }
    return EXIT_SUCCESS;
}