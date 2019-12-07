#include <SFML/Graphics.hpp>
#include "Node.h"
#include "Edge.h"
#include "Traits.h"
#include <string>
#include <algorithm>
#include <unordered_map>
#include <utility>
#include <map> 
#include <cmath>
#include <list>
using namespace std;

#define tamnode 0.3f

template <typename T> 
class Iterator {

  typedef typename T::n_value n_value;
  typedef typename T::e_value e_value;


  private:
      Nodo<n_value,e_value> *current;


  public:
    Iterator() : current(nullptr) {};
    Iterator(Nodo<n_value,e_value> *node) : current(node) {
      
      //cout<<(*current).get_posx()<<endl;
      //cout<<(*current).get_posy()<<endl;
    };
    
    Iterator<T> operator++(){

      //cout<<current->get_posx()<<endl;
      e_value max = std::numeric_limits<e_value>::min();
      e_value act_vecindad = (*current).get_vecindad();
      auto edg = (current->get_edges()).begin();
      auto ite_max = (current->get_edges()).begin();

      /*
      for(; edg!=(current->get_edges()).end();edg++){
        if(max<edg->get_data() and (edg->get_data())<(act_vecindad)){
          max = edg->get_data();
          ite_max = edg;
        }
        cout<<edg->get_data()<<" - "<<act_vecindad<<" - "<<max<<" - "<<(edg->get_to())->get_posx()<<" - "<<(edg->get_to())->get_posy()<<endl;
      }
      */

      current = ite_max->get_to();
      cout<<"EL VALRO ES "<<(*current).get_posx()<<" - "<<current->get_posy()<<endl;

      return *this;
    }

    Iterator<T> operator--(){
      e_value min = std::numeric_limits<e_value>::max();
      e_value act_vecindad = (*current).get_vecindad();
      auto edg = (current->get_edges()).begin();
      auto ite_min = (current->get_edges()).begin();



      for(; edg!=(current->get_edges()).end();edg++){
        if(min>edg->get_data() and (edg->get_data())<(act_vecindad)){
          min = edg->get_data();
          ite_min = edg;
        }
        cout<<edg->get_data()<<" - "<<act_vecindad<<" - "<<max<<" - "<<(edg->get_to())->get_posx()<<" - "<<(edg->get_to())->get_posy()<<endl;
      }


      return *this;
    }

    Nodo<n_value,e_value> operator*(){

      return *(this->current);
    } 


    
};




template< typename T>
class Graph {

private:

  vector<pair<sf::CircleShape *,int>> allcircles;
  vector<sf::VertexArray *> alledges;
  typedef typename T::n_value n_value;
  typedef typename T::e_value e_value;
  

public:

  list<Nodo<n_value,e_value>> _nodes;


  Nodo<n_value, e_value>& get_node(int pos){
    int actual = 0;
    auto it = _nodes.begin();
    for(;actual!=pos;actual++,it++){}
    return *it;
  }

  vector<sf::VertexArray *>& get_lines(){
    return alledges;
  }

  vector<pair<sf::CircleShape *,int>>& get_circles(){
    return allcircles;
  }


  Iterator<T> begin(){
    int pos = rand() % _nodes.size();
    (&get_node(pos))->show();
    return Iterator<T>(&get_node(pos));
  }

  Iterator<Nodo<n_value,e_value>> end(){
    return Iterator<T>();
  }


  


  float calculateEuristic(Nodo<n_value,e_value> *from, Nodo<n_value,e_value> *to){
  
    float heuristic_value = sqrt(pow(((from->get_posx())-(to->get_posx())),2)+pow(((from->get_posy())-(to->get_posy())),2));

    return heuristic_value;
  
  }





  Graph* Astar(Nodo<n_value, e_value> &from, Nodo<n_value, e_value> &to){

    Graph<T> *graphAstar = new Graph<T>;
    //cout<<from.get_value()<<" "<<to.get_value()<<endl;
    Nodo<n_value, e_value> *From = &from;
    Nodo<n_value, e_value> *current = &from;
    Nodo<n_value, e_value> *To = &to;
    
    unordered_map<Nodo<n_value,e_value>*,bool> status;
    
    multimap<float,Nodo<n_value,e_value>*> total_distance;
    unordered_map<Nodo<n_value,e_value>*,pair<e_value,float>> short_euristic;
    unordered_map<Nodo<n_value,e_value>*,Nodo<n_value,e_value>*> path;



    short_euristic[From]=make_pair(0,calculateEuristic(From,To));

    total_distance.insert(make_pair<float,Nodo<n_value,e_value>*&>((short_euristic[From].first + short_euristic[From].second),From));
    path.insert(make_pair(From,From));


    while(current!=To){
      status[current]=true;
      for(auto ac = (current->get_edges()).begin();ac!=(current->get_edges()).end();ac++){
        auto use = ((*ac).get_to());
        if(status.find(use)!=status.end()){
          if(status[use]==true){continue;} 
          e_value temp_short = (short_euristic[current].first)+(*ac).get_data();
          if(temp_short>=short_euristic[use].first){continue;}
            short_euristic[use].first = temp_short;
            path[((*ac).get_to())]=(((*ac).get_from()));
          }

          else{
                status[use]=false;
               
                short_euristic[use]=make_pair<e_value,float>(((short_euristic[current].first)+(*ac).get_data()),calculateEuristic(use,To));
                path.insert(make_pair(( ( (*ac).get_to())),( ( (*ac).get_from()))));
            }
            total_distance.insert(make_pair<float,Nodo<n_value,e_value>*&>((short_euristic[use].first+short_euristic[use].second),use));

        }
        for(auto ac = total_distance.begin();ac != total_distance.end();ac++){
            if((status[ac->second])==false){
                current = ac->second;
                break;
            }
      }
    }

    auto temp = To;
    vector<Nodo<n_value,e_value>*> final_path;
    while(temp != path[temp] ){
        final_path.push_back(temp);
        final_path.push_back(path[temp]);
        path[temp] = path[path[temp]];
        temp = path[temp];
    }
    final_path.push_back(From);

    cout<<"path size es: "<<final_path.size()<<endl;

    for(int i=1;i<final_path.size();i++){
        n_value dato1 = final_path[i-1]->get_value();
        n_value dato2 = final_path[i]->get_value();
        graphAstar->insert_nodes( dato1);
        graphAstar->insert_nodes( dato2);

        graphAstar->insert_edges( dato1, dato2);
    }

    //graphAstar->print();

    //for(auto nod: )


    return graphAstar;
  }



  Graph *dijkstra( Nodo<n_value,e_value> &nodo1, Nodo<n_value,e_value> &nodo2){

    std::cout<<"from ";
    nodo1.show();
    std::cout<<" to ";
    nodo2.show();
    cout<<endl;

    std::map< Nodo<n_value,e_value>*, e_value> dijk;
    std::map<Nodo<n_value,e_value>*,Nodo<n_value,e_value>* > pred;
    std::map<Nodo<n_value,e_value>*, std::string> color;
    std::map<Nodo<n_value,e_value>*, e_value> priory_queue;
    
    Graph<T> *grafdijk = new Graph<T>;

    //for the nodes save in the maps
    for (auto it=_nodes.begin();it!=_nodes.end();++it){
      dijk[&(*it)] = __INT_MAX__;
      color[&(*it)] = "W";
      priory_queue[&(*it)]=dijk[&(*it)];
    }
    auto iti = std::find(_nodes.begin(),_nodes.end(), nodo1);
    auto ito = std::find(_nodes.begin(),_nodes.end(), nodo2);
    
    dijk[&(*iti)] = 0;
    pred[&(*iti)]= &(*iti);
    priory_queue[&(*iti)]=dijk[&(*iti)];
    Nodo<n_value,e_value> * ptr_nodo;

    std::vector<Nodo<n_value,e_value>*> vecnodo ;
    while(!priory_queue.empty()){
      std::pair<Nodo<n_value,e_value>*, int> min = *min_element(priory_queue.begin(), priory_queue.end(), compare);

     // cout<<min.first<<" "<<min.second<<endl;

      priory_queue.erase(min.first);
      ptr_nodo = min.first;

      //(*ptr_nodo).show(); 
      //cout<<dijk[ptr_nodo]<<endl;
      // ptr_nodo.get_edges // get each edge from list edges
      for (auto it=(ptr_nodo->get_edges()).begin(); it!=(ptr_nodo->get_edges()).end();++it){
        if (dijk[ptr_nodo]+ (*it).get_data() < dijk[(*it).get_to()]){
          dijk[(*it).get_to()]= dijk[ptr_nodo]+ (*it).get_data();
          priory_queue[(*it).get_to()]=dijk[(*it).get_to()];
          pred[(*it).get_to()]= ptr_nodo;
        }

        color[ptr_nodo] = "B";
      }
      //vecnodo.push_back(ptr_nodo);

    }
    /*
    auto *temp = &nodo2;
    while(temp!=nullptr){
      cout<<temp->get_value().x<<" - "<<temp->get_value().y<<endl;
      pred[temp] = pred[pred[temp]];
      temp = pred[temp];
    }
    */

    
    auto temp = &nodo2;
    std::list<Nodo<n_value,e_value>* > final_path;
/*
    for(auto elem : pred){
      (*(elem.first)).show();
      (*(elem.second)).show();
    } */
    /*
    for(auto elem : dijk){
      (*(elem.first)).show();
      std::cout << " "<<((elem.second))<< "\n";
    } */

    /*
    for(auto elem : pred){
      (*(elem.first)).show();      
      (*(elem.second)).show();
      cout<<endl;

    }
    */

    
    while(temp != &nodo1 ){
      
        final_path.push_back(temp);
        final_path.push_back((pred[temp]));
        pred[temp] = pred[(pred[temp])];
        temp = pred[temp];
    }
    final_path.push_front(&nodo1);
    cout<<"salio dijkstra"<<endl;
    

    /*
    auto temp = To;
    vector<Nodo<n_value,e_value>*> final_path;
    while(temp != path[temp] ){
        final_path.push_back(temp);
        final_path.push_back(path[temp]);
        path[temp] = path[path[temp]];
        temp = path[temp];
    }
    */

    //crea grafo
    for(int i=0;i<final_path.size()-1;i++){
        n_value dato1 = final_path[i]->get_value();
        n_value dato2 = final_path[++i]->get_value();
        grafdijk->insert_nodes( dato1);
        grafdijk->insert_nodes( dato2);

        grafdijk->insert_edges(dato1, dato2);
    } 

    
  for (auto it=grafdijk->_nodes.begin(); it!=grafdijk->_nodes.end(); ++it){
    (*it).show();
    cout<<endl;
  }
  

    //grafdijk->print();
    return grafdijk;
  }
  static bool compare(std::pair<Nodo<n_value,e_value>* ,int> i, pair<Nodo<n_value,e_value>*, int> j) {
        return i.second < j.second;
    }
  
  

  void lectura(std::string filename){
    std::vector<n_value> vecn = Trait<n_value>::loadNodos(filename);
    for (auto it= vecn.begin(); it!=vecn.end();++it){
      insert_nodes(*it);
    }
    std::vector<pair<int,int>> vece = Trait<n_value>::loadEdges(filename);
    for (auto it= vece.begin();it!=vece.end();++it){
      insert_edges(vecn[(*it).first], vecn[(*it).second]) ;
    }
  }



  void insert_nodes(const n_value& val){
    Nodo<n_value, e_value> node(val);
    sf::CircleShape *newnode = new sf::CircleShape(tamnode);
    newnode->setFillColor(sf::Color(47,79,79));
    newnode->setPosition(val.x,val.y);
    allcircles.push_back(make_pair(newnode,allcircles.size() ) );
    _nodes.push_back(node);
  }  


  void insert_edges( n_value& i,  n_value& o){
    double dist = o-i;
    Nodo<n_value, e_value> nodei(i);
    auto iti = std::find(_nodes.begin(),_nodes.end(), nodei);
    if (iti != _nodes.end()){       
      Nodo<n_value, e_value> nodeo(o);
      auto ito = std::find(_nodes.begin(),_nodes.end(), nodeo);
      if (ito!=_nodes.end()){ //existe nodo 2
        //(*iti).show();
        //(*ito).show();
//        std::cout<< &(*iti)<< " y - ";
        // Construir Edge(&i,&o,e)
        Edge<n_value,e_value> edge((*iti),(*ito),dist);

        sf::VertexArray *lines = new sf::VertexArray(sf::Lines,2);

        (*lines)[0].position = sf::Vector2f(i.x,i.y);
        (*lines)[0].color = sf::Color::White;
        (*lines)[1].position = sf::Vector2f(o.x,o.y);
        (*lines)[1].color = sf::Color::White;

        alledges.push_back(lines);

        // iterador List nodos .push_back(edge)
        (*iti).insert_edge(edge);  
      } 
      else{
        std::cout<<"node 2 not found"<<std::endl;     
      }
    }
    else {
      std::cout<<"node 1 not found"<<std::endl;
    }
    
  } 



  void print(){

    int a = 0;
    for (auto it=_nodes.begin();it!=_nodes.end();++it ){
        cout<<a<< " is the node: ";
        (*it).show();
        cout<<"with prom: "<< (*it).average();
        cout<<endl;
        (*it).print_edge();
        a++;

    }
  }

};
