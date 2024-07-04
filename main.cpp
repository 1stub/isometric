#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include "chunkManager.h"

int main(){
  sf::RenderWindow window(sf::VideoMode(1600, 900), "Isometric", sf::Style::Close);
  
  Perlin p;
  chunkManager cm(p);

  while(window.isOpen()){
    sf::Event e;
    while(window.pollEvent(e)){
      if(e.type == sf::Event::Closed){
        window.close();
      }
    }
    window.clear();
    cm.update(window);
    window.display();
  }
  return 0;
}
