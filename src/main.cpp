#include <random>
#include <SFML/Graphics.hpp>
#include "../debug/cpuUsage.hpp"
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

  float frequency = 0.01;
  int octaves = 8;
  float persistence = 0.3;
  chunkManager cm(p, window, v, octaves, persistence, frequency);

  sf::Clock deltaClock; 
  while(window.isOpen()){
    sf::Event e;
    while(window.pollEvent(e)){
      ImGui::SFML::ProcessEvent(window,e);
      if(e.type == sf::Event::Closed){
        window.close();
      }
    }
    ImGui::SFML::Update(window, deltaClock.restart());

    ImGui::Begin("Options");
    ImGui::SliderInt("Octaves", &octaves, 2, 32);
    ImGui::SliderFloat("Persistence", &persistence, 0.1, 1.5);
    ImGui::SliderFloat("Frequency", &frequency, 0.0f, 0.1f);
    ImGui::End();

    window.clear();
    cm.update(octaves, persistence, frequency);
    ImGui::SFML::Render(window);
    window.display();
  }
  ImGui::SFML::Shutdown();
  return 0;
}
