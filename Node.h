#include <utility>
#include <iostream>
using namespace std;
template<typename T>
class Node{
private:
	//T x;
	//T y;
	pair<T,T> coord;
public:
	Node(T _x, T _y) {
		coord = make_pair(_x,_y);
		/*x = _x;
		y = _y;*/
	}

	void print() {
		cout << x << " " << y << endl;
	}

	pair<T,T> get_coord() {
		return coord;
	}

	bool operator==(Node<T>* copy) {
		return get_coord() == copy->get_coord();
	}

	bool operator!=(Node<T>* copy) {
		return get_coord() != copy->get_coord();
	}
};
