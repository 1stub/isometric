#include <random>
#include <SFML/Graphics.hpp>
#include "../debug/cpuUsage.hpp"
#include "../include/imgui/imgui.h"
#include "../include/imgui/imgui-SFML.h"
#include "chunkManager.h"

int main(){
  sf::RenderWindow window(sf::VideoMode(1600, 900), "Isometric", sf::Style::Close);
  window.setFramerateLimit(60);

  ImGui::SFML::Init(window);

  //logic for creating random number
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(100000, 999999);
  int random_number = dis(gen);

	const siv::PerlinNoise::seed_type seed = random_number;
	const siv::PerlinNoise p{ seed };

  sf::View v(sf::FloatRect(0,0, Game::screenWidth, Game::screenHeight));
  float zoom = 4.0f;
  v.zoom(zoom);

  chunkManager cm(p, window, v);

  sf::Clock deltaClock; 
  while(window.isOpen()){
    sf::Event e;
    while(window.pollEvent(e)){
      if(e.type == sf::Event::Closed){
        window.close();
      }
    }
    window.clear();
    cm.update();
    window.display();
  }
  return 0;
}
