#include <iostream>
#include "Graph.h"
#include <vector>
int main(){
	Graph<double,false> g("100points.vtk");
	g.print_adjacency_list();
	g.delete_node(531,616);
	g.delete_node(451,656);
	g.delete_node(767,613);
	//g.delete_edge(10,10,127,10);
	/*g.print_adjacency_list();
	std::cout << g.densidad() << std::endl;
	std::cout << g.connected() << std::endl;	
	std::cout << g.BFS(10,10) << std::endl;
	g.add_node(5000,5000);
	g.add_edge()*/
	//g.add_node(500,500);
	std::cout << g.grade_of_node(638,206) << std::endl;
	std::cout << g.connected() << std::endl;
	//g.print_adjacency_list();
	return 0;
}
