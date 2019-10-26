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

		//to create the edges
		int n1,n2,n3;
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
*/

	pnode search_node(t x, t y) {
		std::pair<t,t> temp(x,y);
		for(auto it = nodes.begin(); it != nodes.end(); ++it) {
			if((*(*it)) == temp) {
				return *it;
			}
		}
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
			reset_nodes();
		}
		else {
			std::cout << "El nodo no existe\n";
			return cont;
		}
		return cont;
	}

	void reset_nodes() {
		for(auto it = nodes.begin(); it != nodes.end(); ++it) {
			(*it)->set_visited(false);
			(*it)->set_color('N');
		}
	}

	Nodes DFS(t x, t y) {
		std::queue<pnode> Dfs;
		Nodes dfs;
		if(search_node(x,y)) {
			Dfs.push(search_node(x,y));
			Dfs.front()->set_visited(true);
			dfs.push_back(Dfs.front());
			while(!Dfs.empty()) {
				for(auto it = adjacency_list[Dfs.front()]->begin(); it != adjacency_list[Dfs.front()]->end(); ++it) {
					if(!((*it)->get_visited())) {
						(*it)->set_visited(true);
						dfs.push_back((*it));
						Dfs.push((*it));
					}
				}
				Dfs.pop();
			}
			reset_nodes();
			if(dfs.size() == nodes.size()) {
				return dfs;
			}
		}
		else {
			std::cout << "El nodo no existe\n";
		}
	}

	bool isBipartito(){
		map<pnode, char> reg;
		queue<pnode> priority;
		if (nodes.size() == 0)
			return true;
		char color = 1;
		pnode temp;
		priority.push(nodes[0]);
		reg[nodes[0]] = color;
		while(priority.size() > 0) {
			reg[priority.front()] = color;
			for (edge e : priority.front()->edges) {
				temp = e.edgePair(priority.front());
				if (reg[temp->get_data()] == 0)
					priority.push(temp);
				else {
					if (reg[temp->get_data()] != -color)
						return false;
				}
			}
			priority.pop();
			color = -color;
		}
		return true;
	}	    

	pset Neighborhood(t x, t y) {
		pnode search = search_node(x,y);
		if(search) {
			return adjacency_list[search];
		}
		else {
			std::cout << "No existe el nodo.\n";
		}
	}
};
