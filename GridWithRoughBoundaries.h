#ifndef DIJKSTRA_GRID_GRIDWITHROUGHBOUNDARIES_H
#define DIJKSTRA_GRID_GRIDWITHROUGHBOUNDARIES_H

#include <vector>
#include <ostream>
#include <optional>
#include <functional>

// 0,0   0,1   0,2   0,3
//  |     |     |     |
// 1,0 - 1,1 - 1,2 - 1,3
//  |     |     |     |
// 2,0 - 2,1 - 2,2 - 2,3
//  |     |     |     |
// 3,0   3,1   3,2   3,3


struct Vertex
{
    int row;
    int col;
};

std::ostream& operator<<(std::ostream& os, const Vertex& v);

class GridWithRoughBoundaries {
public:
    explicit GridWithRoughBoundaries(int side_nodes_count);


    double edge_weight(const Vertex& s, const Vertex& t) const;
    void edge_weight(const Vertex& s, const Vertex& t, double new_value);

    /// Get a unique label for each vertex
    int label(const Vertex& s) const;
    Vertex vertex_from_label(int l) const;

    void traverse_nodes(const std::function<void(Vertex)>& f) const;
    void traverse_edges(const std::function<void(Vertex,Vertex)>& f) const;

    int nodes_per_side() const {return side_length_;}
    int num_edges() const;

private:
    const int side_length_;
    std::vector<double> weights_;
};



namespace detail
{
    bool are_grid_neighbours(Vertex s, Vertex t);
    std::optional<int> get_storage_index_for_weight(int side_node_count, Vertex s, Vertex t);
    bool are_vertical_boundary_nodes(int side_node_count, Vertex s, Vertex t);
    int compute_num_edges(int side_nodes_count);

}


#endif //DIJKSTRA_GRID_GRIDWITHROUGHBOUNDARIES_H
