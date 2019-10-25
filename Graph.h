#include "Edge.h"
#include "Node.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iostream>
#include <set>
template<typename T>
class Graph{
private:
	vector<Node<T>*> nodes;
	unordered_map<int,Node<T>*> nodes;
	std::vector<Edge<T>*> edges;
public:
	Graph() {
		//for read the file
		ifstream file;
		file.open("pp.vtk");
		int count = 0;
		string line;
		//read line1 
		//until read line 5, porque es el formato vtk
		
		//read line 6 string, np, string
		int np = 6;

		/* //to create the nodes
		Node<T>* temp_nodes = nullptr;
		string _x, _y;
		double x = 0, y = 0;

		//to create the edges
		string node1, node2, node3, helper;
		int n1,n2,n3;
		Edge<T>* temp_edge1 = nullptr;
		Edge<T>* temp_edge2 = nullptr;
		Edge<T>* temp_edge3 = nullptr;
		
		//to create the adjacency list
		set<Node<T>*>* adj_list = nullptr;
		*/
		int nn = 0; //num de nodos
		while(np){
			getline(file,line);
			//lee linea, divide en 3 numeros
			//tengo X y Y y Z vale 0
			nodes[nn] = new node(x,y);
			--np;
			nn++;
		}

		//lee dos lineas en blanco
		//lee string, ne , integer

		int ne = 4;
		while (ne){
			//Lee num de nodos, nodo1, nodo2 ,nodo3 
			//nodo1-> nodo2 , nodo2->nodo3 , nodo3->nodo1
			nodes[nodo1]->addEdge(nodo2);
			nodes[nodo2]->addEdge(nodo3);
			nodes[node3]->addEdge(nodo1);
			ne--;
		}



		
		while(getline(file,line)) {
			count++;
			istringstream tokenizer(line);
			if(count > 6 && count < 11) {
				getline(tokenizer, _x, ' ');
				getline(tokenizer, _y, ' ');
				x = atof(_x.c_str());
				y = atof(_y.c_str());
				temp_nodes = new Node<T>(x,y);
				nodes.push_back(temp_nodes);
				adj_list = new std::set<Node<T>*>;
				adjacency_list.insert({temp_nodes, adj_list});
				temp_nodes = nullptr;
				adj_list = nullptr;
			}
			if(count >= 12 && count < 16) { 
				getline(tokenizer,helper,' ');
				getline(tokenizer,node1,' ');
				getline(tokenizer,node2,' ');
				getline(tokenizer,node3);
				n1 = stoi(node1);
				n2 = stoi(node2);
				n3 = stoi(node3);
				temp_edge1 = new Edge<T>(nodes[n1],nodes[n2]);
				temp_edge2 = new Edge<T>(nodes[n2],nodes[n3]);
				temp_edge3 = new Edge<T>(nodes[n3],nodes[n1]);
				edges.push_back(temp_edge1);
				edges.push_back(temp_edge2);
				edges.push_back(temp_edge3);
				adjacency_list[nodes[n1]]->insert(nodes[n2]);
				adjacency_list[nodes[n2]]->insert(nodes[n3]);
				adjacency_list[nodes[n3]]->insert(nodes[n1]);
				adjacency_list[nodes[n1]]->insert(nodes[n3]);
				adjacency_list[nodes[n2]]->insert(nodes[n1]);
				adjacency_list[nodes[n3]]->insert(nodes[n2]);
				temp_edge1 = nullptr;
				temp_edge2 = nullptr;
				temp_edge3 = nullptr;
			}
		}
	}
	
	void print_nodes() {
		for(auto it = this->nodes.begin(); it != this->nodes.end(); ++it) {
			(*it)->print();
		}
	}

	void p_edges() {
		for(auto it = this->edges.begin(); it != this->edges.end(); ++it) {
			(*it)->print_dist();
		}
	}

	void print_adjacency_list() {
		for(auto it = nodes.begin(); it != nodes.end(); ++it) {
			std::cout << "Node : ";
			(*it)->print();
			std::cout << "Adjacent nodes : ";
			for(auto it2 = adjacency_list[(*it)]->begin(); it2 != adjacency_list[(*it)]->end(); ++it2) {
				(*it2)->print();
			}
		}
	}

	void saveDisk(){
		//escribir las 5 babosadas de linea en file
		//write points , num point, double
		// escribir los puntos X y Y del unorder map
		//

		//escribir cells, num edges /3 , 1720
		//la lista de edges, escribir de 3 en 3
	}
	void degree(){
		
	}
	bool isBipartited(){

	}

	Graph mSTPrim(){
	}

	Graph mSTKruskal(){
	}


	


};

