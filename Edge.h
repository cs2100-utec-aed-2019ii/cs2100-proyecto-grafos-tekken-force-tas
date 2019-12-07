template<typename T, typename E> class Nodo;

template <typename T, typename E> 
class Edge{
  private:
    Nodo<T,E>* from,* to;
    E value; 
  public: 
    Nodo<T,E>* get_from(){return from;}
    Nodo<T,E>* get_to(){return to;}
    E get_data(){return value;}
    Edge(){}
    Edge(Nodo<T,E>& nin, Nodo<T,E>& nout,E dist){
      this->from = &nin;
      this->to = &nout;
      this->value = dist;
    } 
  
};
