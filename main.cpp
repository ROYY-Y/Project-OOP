#include <iostream>
#include "set.h"
#include "map.h"
#include "directed_graph.h"

int main(){
    oop::DirectedGraph g;

    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 4);
    g.addEdge(4, 1);

    std::cout << "Graph:\n";
    g.printGraph();

    std::cout << "BFS from 1: ";
    g.BFS(1);

    std::cout << "DFS from 1: ";
    g.DFS(1);

    std::cout << "Has edge 1->2? " << g.hasEdge(1, 2) << "\n";
    g.removeEdge(1, 2);
    std::cout << "Has edge 1->2 after removal? " << g.hasEdge(1, 2) << "\n";

    g.removeVertex(4);
    std::cout << "Graph after removing vertex 4:\n";
    g.printGraph();

    return 0;
}