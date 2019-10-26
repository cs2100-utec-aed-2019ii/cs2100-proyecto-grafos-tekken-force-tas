#include "Edge.h"
#include "Node.h"
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iostream>																																																													 
#include <set>
#include <utility>
#include <queue>

template<bool T>
struct Directed_Trait {
    static const bool directed = true;
};

template<>
struct Directed_Trait<false> {
    static const bool directed = false;
};
	
template<typename T,bool F>
class Graph{
public:
	typedef Graph<T,F> G;
	typedef T t;
	typedef Node<G>* pnode;
	typedef Node<G> node;
	typedef Edge<G>* pedge;
	typedef Edge<G> edge;
	typedef std::vector<pnode> Nodes;
	typedef std::vector<pedge> Edges;
	typedef std::set<pnode>* pset;
	typedef std::set<pnode> set;
	typedef std::unordered_map<pnode,pset> AList;
private:
<<<<<<< HEAD
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
=======
	Nodes nodes;
	Edges edges;
	AList adjacency_list;
public:
	Graph(std::string namefile) {
		//to read the file
		std::fstream file;
		file.open(namefile);
		std::string line;

		//to create the nodes
		pnode temp_nodes = nullptr;
		t x = 0, y = 0, z = 0;
>>>>>>> develop

		//to create the edges
		int n1,n2,n3;
<<<<<<< HEAD
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
=======
		pedge temp_edge1 = nullptr;
		pedge temp_edge2 = nullptr;
		pedge temp_edge3 = nullptr;

		//to create the adjacency list
		pset adj_list = nullptr;

		//auxiliares
		std::string trash;
		int num_nodes;
		int num_edges;

		for(int i = 0; i < 5; i++) {
			std::getline(file,line);
>>>>>>> develop
		}
		
		file >> line >> num_nodes >> trash;
		for(int i = 0; i < num_nodes; i++) {
			file >> x >> y >> z;
			temp_nodes = new node(x,y);
			nodes.push_back(temp_nodes);
			adj_list = new set;
			adjacency_list.insert({temp_nodes, adj_list});
			temp_nodes = nullptr;
			adj_list = nullptr;
		}

		std::getline(file,line);
		std::getline(file,line);
		
		file >> line >> num_edges;
		int ordures;
		for(int i = 0; i < num_edges; i++) {
			file >> ordures >> n1 >> n2 >> n3;
			temp_edge1 = new edge(nodes[n1],nodes[n2]);
			temp_edge2 = new edge(nodes[n2],nodes[n3]);
			temp_edge3 = new edge(nodes[n3],nodes[n1]);
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

	Graph() {

	}

	Graph(const G& copy) {
		nodes = copy.get_nodes();
		edges = copy.get_edges();
		adjacency_list = copy.get_adj_list();
	}
		
	void save() {

	}

	Nodes get_nodes() {
		return nodes;
	}

	Edges get_edges() {
		return edges;
	}

	AList get_adj_list() {
		return adjacency_list;
	}

	void print_adjacency_list() {
		for(auto it = nodes.begin(); it != nodes.end(); ++it) {
			std::cout << "Node : ";
			(*it)->print();
			std::cout << "Adjacent nodes : ";
			for(auto it2 = adjacency_list[(*it)]->begin(); it2 != adjacency_list[(*it)]->end(); ++it2) {
				(*it2)->print();
			}
			std::cout << "\n";
		}
	}

	bool add_node(t x, t y) {
		pnode in = new node(x,y);
		pset _in = new set;
		for(auto it = nodes.begin(); it != nodes.end(); ++it) {
			if((*in) == *(*it))
				return false;
		}
		nodes.push_back(in);
		adjacency_list.insert({in,_in});
		return true;
	}
/*
	void add_edge(pnode a, pnode b) {
		add_node(a);
		add_node(b);
		pedge in = new edge(a,b);
		edges.push_back(in);
		adjacency_list[a]->insert(b);
		adjacency_list[b]->insert(a);
	}

	bool add_edge(pedge in) {
		edges.push_back(in);
		std::pair<pnode,pnode> get = in.get_nodes();
		add_node(get.first);
		add_node(get.second);
	}
<<<<<<< HEAD

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


	


=======
*/

	pnode search_node(t x, t y) {
		std::pair<t,t> temp(x,y);
		for(auto it = nodes.begin(); it != nodes.end(); ++it) {
			if((*(*it)) == temp) {
				std::cout << "G\n";
				return *it;
			}
		}
		std::cout << "N\n";
		return nullptr;
	}

	bool add_edge(t x, t y, t _x, t _y) {
		pnode in1 = new node(x,y);
		pnode in2 = new node(_x,_y);
		add_node(in1);
		add_node(in2);
		pedge in3 = new edge(in1,in2);
		edges.push_back(in3);
		adjacency_list[in1]->insert(in2);
		adjacency_list[in2]->insert(in1);
	}

	void delete_node(t x, t y) {
		std::pair<t,t> temp(x,y);
		pset temp2 = nullptr;
		pnode temp3 = nullptr;
		for(auto it = nodes.begin(); it != nodes.end(); ) {
			if((*(*it)) == temp) {
				temp3 = (*it);
				it = nodes.erase(it);
				break;
			} else {
				++it;
			}
		}
		for(auto it = edges.begin(); it != edges.end(); ) {
			if((*((*it)->get_nodes().first)) == temp || (*((*it)->get_nodes().second) == temp)) {
				it = edges.erase(it);
			} else {
				++it;
			}
		}

		for(auto it = adjacency_list.begin(); it != adjacency_list.end(); ) {
			if((*(it->first)) == temp) {
				temp2 = it->second;
				it = adjacency_list.erase(it);
				break;
			} else {
				++it;
			}
		}

		for(auto it = temp2->begin(); it != temp2->end(); ++it) {
			for(auto it2 = adjacency_list[(*it)]->begin(); it2 != adjacency_list[(*it)]->end(); ) {
				if((*(*it2)) == temp) {
					it2 = adjacency_list[(*it)]->erase(it2);
					break;
				} else {
					++it2;
				}
			}
		}
		std::cout << "Nodo eliminado " << x << " " << y << std::endl;
		delete temp2;
		delete temp3;
	}

	void delete_edge(t x, t y, t _x, t _y) {
		pnode n1 = search_node(x,y);
		pnode n2 = search_node(_x,_y);
		std::pair<pnode,pnode> search(n1,n2);
		for(auto it = edges.begin(); it != edges.end(); ) {
			if((*(*it)) == search) {
				it = edges.erase(it);
			} else {
				++it;
			}
		}

		for(auto it = adjacency_list[n1]->begin(); it != adjacency_list[n1]->end(); ) {
			if((*(*it)) == n2) {
				it = adjacency_list[n1]->erase(it);
				break;
			} else {
				++it;
			}
		}

		for(auto it = adjacency_list[n2]->begin(); it != adjacency_list[n2]->end(); ) {
			if((*(*it)) == n1) {
				it = adjacency_list[n2]->erase(it);
				break;
			} else {
				++it;
			}
		}
	}

	double grade_of_node(t x, t y) {
		pnode n1 = search_node(x,y);
		double count = adjacency_list[n1]->size();
		return count;
	}

	double densidad() {
		double densidad = (double)(2*edges.size())/((nodes.size()*(nodes.size()-1)));
		return densidad;
	}

	bool connected() {
		for(auto it = adjacency_list.begin(); it != adjacency_list.end(); ) {
			if((it->second)->size() == 0) {
				return false;
			} else {
				++it;
			}
		}
		return true;
	}

	double BFS(t x, t y) {
		double cont = 0;
		std::queue<pnode> Bfs;
		if(search_node(x,y)) {
			Bfs.push(search_node(x,y));
			Bfs.front()->set_visited(true);
			while(!Bfs.empty()) {
				for(auto it = adjacency_list[Bfs.front()]->begin(); it != adjacency_list[Bfs.front()]->end(); ++it) {
					if(!((*it)->get_visited())) {
						(*it)->set_visited(true);
						cont++;
						Bfs.push((*it));
					}
				}
				Bfs.pop();
			}
		}
		else {
			std::cout << "El nodo no existe\n";
			return cont;
		}
		return cont;
	}

	double DFS() {
		
	}	
>>>>>>> develop
};

