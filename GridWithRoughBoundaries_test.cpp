#include "GridWithRoughBoundaries.h"
#include <cassert>
#include <cstring>
#include <iostream>

int main()
{

    // 0,0   0,1   0,2   0,3
    //  |     |     |     |
    // 1,0 - 1,1 - 1,2 - 1,3
    //  |     |     |     |
    // 2,0 - 2,1 - 2,2 - 2,3
    //  |     |     |     |
    // 3,0   3,1   3,2   3,3


    const size_t k_gsize = 7;
    GridWithRoughBoundaries g(k_gsize);

    try {
        g.edge_weight({0,0},{0,1},1);
    }
    catch(std::exception& e)
    {
        assert(strcmp("Nodes not neighbours of grid: Vertex{0,0} and Vertex{0,1}",e.what())==0);
    }




    int counter = 0;
    g.traverse_edges([&](Vertex s, Vertex t){
//      std::cout << s << t
//                << *detail::get_storage_index_for_weight(k_gsize, s, t)
//                << std::endl;
      g.edge_weight(s, t, counter++);
    });


    counter = 0;
    g.traverse_edges([&](Vertex s, Vertex t){
        assert(*detail::get_storage_index_for_weight(k_gsize, s, t)==counter);
        assert((g.edge_weight(s,t)==counter++));
    });


    return 0;
}