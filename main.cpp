#include <iostream>
#include "Graph.h"
#include <vector>
int main(){
	Graph<double,false> g("pp.vtk");
	g.print_adjacency_list();
	g.delete_node(10,127);
	g.delete_edge(10,10,127,10);
	g.print_adjacency_list();
	std::cout << g.densidad() << std::endl;
	std::cout << g.connected() << std::endl;	
	//g.bipartited();
	std::cout << g.BFS(10,10) << std::endl;
	return 0;
	
}
