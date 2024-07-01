#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Vector2.hpp>
#include "map.h"

int main(){
  sf::RenderWindow window(sf::VideoMode(1600, 900), "Topdown", sf::Style::Close);
    Map map(10, 10, 32);
    map.loadTileset("grass.png");
    
    int size = 10;

  // Initialize the map with some tiles  
  map.setTile(size, size, 0, 1600, 900, size); // Example tile setting

  while(window.isOpen()){
    sf::Event e;
    while(window.pollEvent(e)){
      if(e.type == sf::Event::Closed){
        window.close();
      }
    }
    window.clear();
    map.updateAndDraw(window);
    window.display();
  }
  return 0;
}
