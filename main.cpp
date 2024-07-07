#include <SFML/Graphics.hpp>
#include "chunkManager.h"

int main(){
  sf::RenderWindow window(sf::VideoMode(1600, 900), "Isometric", sf::Style::Close);

	const siv::PerlinNoise::seed_type seed = 123456u;

	const siv::PerlinNoise p{ seed };

  sf::View view(sf::FloatRect(0,0,1600,900));
  chunkManager cm(p);

  sf::Clock clock;
  
  while(window.isOpen()){
    sf::Event e;
    while(window.pollEvent(e)){
      if(e.type == sf::Event::Closed){
        window.close();
      }
    }
    sf::Time deltaTime = clock.restart();
    
    window.clear();
    cm.update(window, view, deltaTime);
    window.display();
  }
  return 0;
}
