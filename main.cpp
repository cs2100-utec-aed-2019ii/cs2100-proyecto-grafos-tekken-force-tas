#include <iostream>
#include "Graph.h"
#include <vector>
int main(){
	Graph<double,false> g("100points.vtk");
	g.print_adjacency_list();
	std::cout << g.densidad() << std::endl;
	std::cout << g.connected() << std::endl;	
	std::cout << g.BFS(600,400) << std::endl;
	auto imdfs = g.DFS(600,200);
	for(auto it = imdfs.begin(); it != imdfs.end(); ++it) {
		(*it)->print();
	}
	auto neighborhood = g.Neighborhood(700,700);
	for(auto it = neighborhood->begin(); it != neighborhood->end(); ++it) {
		(*it)->print();
	}
	std::cout << std::endl;
	std::cout << g.isBipartito() << std::endl;
	//g.delete_node(900,0);
	//g.delete_edge(10,10,127,10);
	g.print_adjacency_list();
	return 0;
}
