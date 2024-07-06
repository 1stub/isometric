#include <SFML/Graphics.hpp>
#include "chunkManager.h"

int main(){
  sf::RenderWindow window(sf::VideoMode(1600, 900), "Isometric", sf::Style::Close);

  Perlin p;
  chunkManager cm;

  cm.update(p);

  while(window.isOpen()){
    sf::Event e;
    while(window.pollEvent(e)){
      if(e.type == sf::Event::Closed){
        window.close();
      }
    }
    window.clear();
    cm.render(window);
    window.display();
  }
  return 0;
}
