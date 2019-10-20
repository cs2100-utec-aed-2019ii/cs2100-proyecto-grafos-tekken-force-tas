#include <iostream>
#include "Graph.h"
#include <vector>
int main(){
	Graph<double> g;
	/*g.print_nodes();
	g.p_edges();*/
	g.print_adjacency_list();
	/*char d = 0;
	std::cin>>d;
	std::vector<float> k;
	for(int i = 0; i < 128; i++) {
		k.push_back((float)i);
	}
	std::cout << k[d] << std::endl;*/
	return 0;
}
