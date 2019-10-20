//#include "Node.h"
#include <utility>
#include <cmath>
#include <iostream>
using namespace std;
template<typename T>
class Edge{
private:
	pair<Node<T>*,Node<T>*> vertices;
	T distancia;
public:
	Edge(Node<T>* a, Node<T>* b) {
		this->vertices = make_pair(a,b);
		pair<T,T> coord_a = a->get_coord();
		pair<T,T> coord_b = b->get_coord();
		this->distancia = sqrt(pow(coord_a.first-coord_b.first,2)+pow(coord_a.second-coord_b.second,2));
	}
	void print_dist() {
		cout << distancia << endl;
	}
};
