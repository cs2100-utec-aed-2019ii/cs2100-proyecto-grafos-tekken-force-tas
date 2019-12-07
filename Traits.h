#include <math.h>
#include <string>
#include <vector>
#include <stdlib.h>
#include <fstream>
#include <iostream>
#include <utility> 

using namespace std;
class Coordenada{
  public:
    int x; int y;
    friend double operator-(Coordenada& ,Coordenada&); 

    bool operator==(const Coordenada&c1){
      
        return this->x ==c1.x && this->y ==c1.y ;
    }
    friend ostream & operator<<(ostream &out, const Coordenada &c);

};
ostream & operator << (ostream &out, const Coordenada &c)
{
    out <<"("<< c.x<<","<<c.y<<")";
    return out;
}

double operator-(Coordenada &c1,Coordenada &c){
      return sqrt( pow((c1.x- c.x),2)+ pow((c1.y-c.y),2) ) ;
}


class myString{
  public:
    string val;

    double operator-(myString c){
      return 0 ;//leveihnteing(c.val- val);
    }
};

template<typename T>
class Trait{ //trait general
  public:
  typedef T n_value;
  typedef double e_value;
  //helpers
  std::vector<n_value> loadNodos(string s){}
  std::vector<int> loadEdges(string s){}
};

template<>
class Trait<Coordenada>{ //de coordenada
  public:
  typedef Coordenada n_value;
  typedef double e_value;

  static std::vector<n_value> loadNodos(string filename){
    std::vector<n_value> vecvalues;
    std::string cad;
    ifstream file(filename);
    int numPuntos;
    while (!file.eof()){
      file >> cad;
      if (cad.compare("POINTS")==0){ //cad = "POINTS"      
        //leo cantidad ed puntos
        file >> cad;
        int numPuntos = std::atoi(cad.c_str());
      
        file>>cad;
        n_value value;

        for (int i=0;i<numPuntos;i++){
          file >> cad ;//X
          value.x = atoi(cad.c_str());
          file >> cad ;//Y
          value.y = atoi(cad.c_str());
          file >> cad ;
          vecvalues.push_back(value);
        }     
      } 
    }
    file.close();    
    return vecvalues;
  }


  static std::vector<pair<int,int>> loadEdges(string filename){
    std::string cad;
    ifstream file(filename);
    std::vector<pair<int,int>> vece; //vector de edges
    while (!file.eof()){
      file>>cad;
      if (cad.compare("CELLS")==0){ //cad = "POINTS"
        file>>cad;
        int numLineas = std::atoi(cad.c_str());
        file>>cad;
        for (int i=0; i<numLineas; i++){
          std::vector<int> vecaux{}; //guarda cada linea 
          file>>cad;
          int numDeEdges = std::atoi(cad.c_str());
          for (int a=0; a<numDeEdges;a++){
            file>>cad;
            int nod1 = std::atoi(cad.c_str());
            vecaux.push_back(nod1);
          }
          vecaux.push_back(vecaux[0]);
          //vecaux
          //6 : 9 11 25 35 45 6  + 9         
          for (int x=0; x<vecaux.size()-1;x++ ){
            //cout<<"ga"<<endl;
            vece.push_back(make_pair(vecaux[x],vecaux[x+1]));
            
          } 
        }    
        
      }
    } 
    file.close();
    return vece;
  }

};


template<>
class Trait<myString>{ //de coordenada
  public:
  typedef myString n_value;
  typedef double e_value;
  //helpers

  static void load(){
    // TODO
  }
}; 

