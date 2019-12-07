#include <iostream>
#include "Graph.h"
#include <time.h> 

#define height 1700 
#define width 900


int main()
{
  sf::RenderWindow window(sf::VideoMode(height, width), "SFML works!");
  sf::View view(sf::FloatRect(0, 0, 500, 500));
  srand (time(NULL));
  
  //boingo_mesh_image_rgb_cell_data
  //binary_fire_symbolmesh_image
  //sf::CircleShape shape(100.f);
  typedef Trait<Coordenada> trait_t;
  typedef Trait<string> trait_2;
  Graph<trait_t> graph;
  graph.lectura("binary_fire_symbolmesh_image.vtk");
  //std::cout<<"leyo grafo"<<std::endl ;
  window.setView(view);
  //graph.print();

  bool leftpressed = false;
  bool rightpressed = false;
  bool Astar = false;
  bool Dijkstra = false;
  int pos_nodefrom;
  int pos_nodeto;

  Iterator<trait_t> it = graph.begin();
  //(*it).show();
  //cout<<(*it).get_posx()<<" - "<<(*it).get_posy()<<endl;
  //++it;
  Graph<trait_t> *Nuevo = nullptr;
  auto val1 = graph._nodes.begin();
  auto val2 = ++graph._nodes.begin();
  for(int i=0;i<700;++val2,i++);
  //Graph<trait_t> *Nuevo = graph.Astar(*val1,*val2);
//Nuevo->print();

  //shape.setFillColor(sf::Color::Green);

  while (window.isOpen())
  {
      sf::Event event;
      while (window.pollEvent(event))
      {
          if (event.type == sf::Event::Closed)
              window.close();
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
              view.zoom(1.04f);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::O)){
              view.zoom(0.95f);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::I)){
              view.move(0.f, -3.f);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::K)){
              view.move(0.f, 3.f);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
              view.move(-3.f, 0.f);
          }
          if (sf::Keyboard::isKeyPressed(sf::Keyboard::L)){
              view.move(3.f, 0.f);
          }



          if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) and leftpressed==true and rightpressed == true){
              cout<<"entro al A star"<<endl;
              Nuevo = graph.Astar(graph.get_node(pos_nodefrom),graph.get_node(pos_nodeto));
              //Nuevo = grpah.Astar(graph.get)
              leftpressed=false;
              rightpressed=false;
          }

          if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) and leftpressed==true and rightpressed == true){
              cout<<"entro al D star"<<endl;
              Nuevo = graph.dijkstra(graph.get_node(pos_nodefrom),graph.get_node(pos_nodeto));
              //Nuevo = grpah.Astar(graph.get)
              leftpressed=false;
              rightpressed=false;
          }

          if(sf::Mouse::isButtonPressed(sf::Mouse::Left) and leftpressed==false){
            Nuevo = nullptr;
            sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
          
            for(auto val : graph.get_circles()){
              sf::FloatRect bounds = (*(val.first)).getGlobalBounds();
              if(bounds.contains(mouse)){
                pos_nodefrom=((val.second));
                //cout<<"left: "<<((val.second))<<endl;
                leftpressed=true;
                break;
              }
            }

          }

          if(sf::Mouse::isButtonPressed(sf::Mouse::Right) and rightpressed==false){
            sf::Vector2f mouse = window.mapPixelToCoords(sf::Mouse::getPosition(window));
          
            for(auto val : graph.get_circles()){
              sf::FloatRect bounds = (*(val.first)).getGlobalBounds();
              if(bounds.contains(mouse)){
                
                rightpressed=true;
                pos_nodeto = ((val.second));
                
                break;
              }
            }
          }

      }
      window.setView(view);
      window.clear();


      for(auto lin : graph.get_lines()){
        (*lin)[0].color = sf::Color::Yellow;
        (*lin)[1].color = sf::Color::Red;
        window.draw(*lin);
      }

      if(Nuevo!=nullptr){
        //cout<<"sie entra aca"<<endl;
        for(auto lin : Nuevo->get_lines()){
          window.draw(*lin);
        }

        for(auto cir : Nuevo->get_circles()){
          //newnode->setFillColor(sf::Color(47,79,79));
          ((cir.first))->setScale(7.f,7.f);
          ((cir.first))->setFillColor(sf::Color(200,200,200));
          window.draw(*(cir.first));
        }

      }
      

      for(auto cir : graph.get_circles()){
        window.draw(*(cir.first));
      }

      window.display();
  }

  return 0;
}
