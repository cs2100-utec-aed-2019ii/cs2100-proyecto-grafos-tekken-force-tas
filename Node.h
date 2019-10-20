#include <utility>
#include <iostream>
using namespace std;
template<typename T>
class Node{
private:
	T x;
	T y;
public:
	Node(T _x, T _y) {
		this->x = _x;
		this->y = _y;
	}
	void print() {
		cout << x << " " << y << endl;
	}

	pair<T,T> get_coord() {
		return make_pair(this->x,this->y);
	}
};
