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
#include <map>

template<bool T>
struct Directed_Trait {
    static const bool directed = true;
};

template<>
struct Directed_Trait<false> {
    static const bool directed = false;
};
	
template<typename T, bool F>
struct camp;

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
		int n;
		file >> line >> num_edges >> n;
		int ordures;
		for(int i = 0; i < num_edges; i++) {//se cambian el tercer indice del CELLS para cuando querramos crear bipartitos
			if(n == 1) {//para cuando son 3 coordenadas
				file >> ordures >> n1 >> n2 >> n3;
				temp_edge1 = new edge(nodes[n1],nodes[n2]);
				temp_edge2 = new edge(nodes[n2],nodes[n3]);
				temp_edge3 = new edge(nodes[n3],nodes[n1]);
				nodes[n1]->add_edge(temp_edge1);
				nodes[n2]->add_edge(temp_edge2);
				nodes[n3]->add_edge(temp_edge3);
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
			if(n == 0) {//para cuando son 2 coordenadas
				file >> ordures >> n1 >> n2;
				temp_edge1 = new edge(nodes[n1],nodes[n2]);
				nodes[n1]->add_edge(temp_edge1);
				edges.push_back(temp_edge1);
				adjacency_list[nodes[n1]]->insert(nodes[n2]);
				adjacency_list[nodes[n2]]->insert(nodes[n1]);
			}
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
		pnode search = search_node(x,y);
		Edges borrar;
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
		int cont = 0;
		for(auto it = nodes.begin(); it != nodes.end(); ++it) {
			std::cout << "Contador : " << cont << std::endl;
			for(auto it2 = ((*it)->get_edges()).begin(); it2 != ((*it)->get_edges()).end(); ++it2) {
				if((*(*it2)) == search) {
				//	it2 = ((*it)->get_edges()).erase(it2);
					(*it2)->print_weight();
					search->print();
					std::cout << "Borrado" << std::endl;
				}
				/*else {
					++it2;
					std::cout << "No es borrado" << std::endl;
				}*/
			}
			cont++;
		}

		for(auto it = edges.begin(); it != edges.end(); ) {
			if((*((*it)->get_nodes().first)) == temp || (*((*it)->get_nodes().second) == temp)) {
				borrar.push_back((*it));
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

		for(auto it = borrar.begin(); it != borrar.end(); ++it) {
			delete (*it);
		}
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
			reset_nodes(x,y);
		}
		else {
			std::cout << "El nodo no existe\n";
			return cont;
		}
		return cont;
	}

	void reset_nodes(t x, t y) {
		for(auto it = nodes.begin(); it != nodes.end(); ++it) {
			(*it)->set_visited(false);
			(*it)->set_color('N');
		}
	}

	Nodes DFS(t x, t y) {
		std::queue<pnode> Dfs;
		Nodes dfs;
		Nodes error;
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
			reset_nodes(x,y);
			if(dfs.size() == nodes.size()) {
				return dfs;
			}
			else {
				return error;
			}
		}
		else {
			std::cout << "El nodo no existe\n";
			return error;
		}
	}	

	pset Neighborhood(t x, t y) {
		pnode search = search_node(x,y);
		if(search) {
			return adjacency_list[search];
		}
		else {
			std::cout << "No existe el nodo.\n";
			return nullptr;
		}
	}

	bool isBipartito(){
        std::map<pnode, int> reg;
        std::queue<pnode> priority;
        if (nodes.size() == 0)
            return true;
        int color = 1;
        pnode temp = nullptr;
        priority.push(nodes[0]);
        reg.insert({nodes[0], color});
        while(priority.size() > 0) {
            reg[priority.front()] = color;
            for (auto e : (priority.front())->get_edges()) {
                temp = e->edgePair(priority.front());
                if (reg[temp] == 0)
                    priority.push(temp);
                else {
                    if (reg[temp] != -color)
                        return false;
                }
            }
            priority.pop();
            color = -color;
        }
        return true;
    }


	AList * kruskal() {
		//ASSERT(is_conexo(), "El grafo no es conexo");
		std::map<pnode, pnode> reg;
		std::set<pedge, camp<t,F>> edges;
		for(auto&& nit : nodes){
			reg[nit] = 0;
			for (auto&& eit : nit->get_edges())
				edges.insert(eit);
		}
		AList new_graph;
		for (auto it : edges){
			if (disjoint_set(reg, (it->get_nodes).first, (it->get_nodes).second) )
						new_graph[(*it)->get_nodes().first]->insert((*it)->get_nodes().first);
			}
		edges.clear();
		reg.clear();
		return new_graph;
	}



    bool disjoint_set(std::map<pnode, pnode> &reg, pnode data_1, pnode data_2) {
	    pnode par_1 = get_parent(reg, data_1);
	    pnode par_2 = get_parent(reg, data_2);
	    
	    if (par_1 != par_2)
	        reg[par_1] = par_2;
	    
	    return par_1 != par_2;
	}

    pnode get_parent(std::map<pnode, pnode> &reg, pnode data) {
            if (reg[data] == 0) {
                reg[data] = data;
                return data;
            }

            pnode temp = data;
            
            while(temp != reg[temp])
                temp = reg[temp];
            reg[data] = temp;
            return temp;
    }

};

template<typename T, bool F>
struct camp{
public:
    bool operator() (Edge<Graph<T,F>>* lhs,Edge<Graph<T,F>>* rhs) const {
        if (lhs->get_weigth() == rhs->get_weigth()) { //compara pesos

            if ( (((lhs->get_nodes()).first)->get_coord()) ==  (((rhs->get_nodes()).first)->get_coord()) )
                return (((lhs->get_nodes()).second)->get_coord()) < (((rhs->get_nodes()).second)->get_coord());
            else
                return (((lhs->get_nodes()).first)->get_coord()) <  (((rhs->get_nodes()).first)->get_coord());
        }
        return lhs->get_weigth() < rhs->get_weigth(); // devuelve si derecha es mayor o no 
    }
};