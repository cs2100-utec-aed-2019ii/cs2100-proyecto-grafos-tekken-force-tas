#include <utility>
#include <iostream>
#include <vector>
template<typename Graph>
class Node{
public:
	typedef typename Graph::pnode pnode;
	typedef typename Graph::node node;
	typedef typename Graph::t T;
	typedef typename Graph::pedge pedge;
	typedef typename Graph::edge edge;
	typedef typename Graph::Edges Edges;
private:
	std::pair<T,T> coord;
	bool visited;
	char color;
	Edges e;
public:
	Node(T _x, T _y) {
		coord = std::make_pair(_x,_y);
		visited = false;
	}

	void add_edge(pedge insert) {
		e.push_back(insert);
	}

	void print() {
		std::cout << "(" << coord.first << " " << coord.second << ")" << " ";
	}

	std::pair<T,T> get_coord() {
		return coord;
	}

	bool operator==(pnode copy) {
		return get_coord() == copy->get_coord();
	}

	bool operator==(std::pair<T,T> compare) {
		if(compare.first == coord.first && compare.second == coord.second)
			return true;
		else
			return false;
	}

	bool operator!=(pnode copy) {
		return get_coord() != copy->get_coord();
	}

	void set_visited(bool a) {
		visited = a;
	}

	bool get_visited() {
		return visited;
	}

	void set_color(char c) {
		color = c;
	}

	char get_color() {
		return color;
	}
};
