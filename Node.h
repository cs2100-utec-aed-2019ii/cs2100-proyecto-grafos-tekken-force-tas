#include <utility>
#include <iostream>
template<typename Graph>
class Node{
public:
	typedef typename Graph::pnode pnode;
	typedef typename Graph::node node;
	typedef typename Graph::t T;
private:
	std::pair<T,T> coord;
public:
	Node(T _x, T _y) {
		coord = std::make_pair(_x,_y);
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
};
