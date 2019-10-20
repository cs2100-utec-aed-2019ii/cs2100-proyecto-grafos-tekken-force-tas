#include "node.h"
//#include "edge.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iostream>
template<typename T>
class Graph{
private:
	vector<Node<T>*> container;
	unordered_map<int,Node<T>*> cc;//aun falta ver esto
public:
	Graph() {
		fstream file;
		file.open("pp.vtk");
		string line;
		Node<T>* temp = nullptr;
		int count = 0;
		string _x, _y;
		double x = 0, y = 0;
		while(getline(file,line)) {
			count++;
			istringstream tokenizer(line);
			if(count > 6) {
				getline(tokenizer, _x, ' ');
				getline(tokenizer, _y, ' ');
				//getline(tokenizer, z);
				x = atof(_x.c_str());
				y = atof(_y.c_str());
				temp = new Node<T>(x,y);
				this->container.push_back(temp);
				this->cc[count] = temp;
				temp = nullptr;
			}
		}
	}
	void print_nodes() {
		for(auto it = this->container.begin(); it != this->container.end(); ++it) {
			(*it)->print();
		}
	}
};
