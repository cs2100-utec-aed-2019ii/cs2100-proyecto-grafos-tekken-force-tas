#include <list>

using namespace std;
template <typename T, typename E> class Edge;

template<typename T, typename E> 
class Nodo{
private:
  T value;
  list< Edge<T,E> > _edges;
  double promVecindad;

public:
  Nodo(){}
  explicit Nodo(T val) {
          this->value=val;
          this->promVecindad=0;
  }
  bool operator==(const Nodo<T,E> &nodo) {
    return (this->value == nodo.value);
  } 

  void show(){
    std::cout<<this->value;
  }   

  list<Edge<T,E>>& get_edges(){return _edges;}

  int get_posx(){return value.x;}
  int get_posy(){return value.y;}
  E get_vecindad(){

    promVecindad = average();
    return promVecindad;
  }


  T get_value(){return value;}


  void insert_edge(Edge<T,E> &edge){
    _edges.push_back(edge); 
    
  }



  E average(){
    E av = 0.0;
    for (auto it=_edges.begin();it!=_edges.end();++it){
        av += (*it).get_data();
    }
    if(av==0) return 0;

    return av/_edges.size() ;
  }




  void print_edge(){    
    for (auto it= _edges.begin();it!=_edges.end();++it){
        ((*it).get_from())->show();
        cout<<" -> ";
        ((*it).get_to())->show();
        cout<<" W:"<<(*it).get_data()<<endl;
        cout<<endl;


    }
  }

  /*
  &Nodo operator=(const Nodo &nodo){
    if (this != &nodo){
      delete[] ;


    }
    return *this;
  }
  */

};