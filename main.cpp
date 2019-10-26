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
	std::cout << g.BFS(13,13) << std::endl;
	auto imdfs = g.DFS(13,13);
	for(auto it = imdfs.begin(); it != imdfs.end(); ++it) {
		(*it)->print();
	}
	auto neighborhood = g.Neighborhood(409.18,390);
	for(auto it = neighborhood->begin(); it != neighborhood->end(); ++it) {
		(*it)->print();
	}
	return 0;
}
