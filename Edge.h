#include <utility>
#include <cmath>
#include <iostream>
template<typename Graph>
class Edge{
public:
	typedef typename Graph::pnode pnode;
	typedef typename Graph::node node;
	typedef typename Graph::pedge pedge;
	typedef typename Graph::edge edge;
	typedef typename Graph::t T;
private:
	pnode from;
	pnode to;
	T weight;
public:
	Edge(pnode a, pnode b) {
		this->from = a;
		this->to = b;
		std::pair<T,T> coord_a = a->get_coord();
		std::pair<T,T> coord_b = b->get_coord();
		this->weight = sqrt(pow((float)coord_a.first-(float)coord_b.first,2)+pow((float)coord_a.second-(float)coord_b.second,2));
	}
	void print_weight() {
		std::cout << weight << std::endl;
	}

	std::pair<pnode,pnode> get_nodes() {
		return std::make_pair(this->from, this->to);
	}

	bool operator==(std::pair<pnode,pnode> coord) {
		if(coord.first == this->from && coord.second == this->to)
			return true;
		if(coord.second == this->to && coord.first == this->from)
			return true;
		else
			return false;
	}

	pnode edgePair(pnode ptr){
		return ptr == from ? to : from ;  
	}

	bool operator==(pedge d) {
		pnode from = d.get_nodes().first;
		pnode to = d.get_nodes().second;
		if(from == this->from && to == this->to)
			return true;
		if(from == this->to && to == this->from)
			return true;
		else
			return false;
	}
};
