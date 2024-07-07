#include "chunkManager.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <sstream>
#include <string>

const int w = 32;
const int h = 32;

chunkManager::chunkManager(const siv::PerlinNoise &perlin) : p(perlin){
  screenCenter = sf::Vector2f(SCREEN_WIDTH/2 - 16, SCREEN_HEIGHT/2 - 16);

  if (!font.loadFromFile("Eight-Bit Madness.ttf")) {
    std::cout << "font err" << std::endl;
  }
  text.setFont(font);
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);
  text.setPosition(10, 10);

  loadChunks();
}

void chunkManager::loadChunks(){
  for(int i = -renderLimit; i < renderLimit; i++){
    for(int j = -renderLimit; j < renderLimit; j++){
      auto chunk = std::make_shared<Chunk>(16);
      chunk->setBlocks(i*16,j*16, p);
      chunk->scale(0.25f, 0.25f);
      std::string coord = std::to_string(i) + "," + std::to_string(j);
      chunks.push_back({coord, chunk});
    }
  }
      std::cout << "Total chunks loaded: " << chunks.size() << std::endl;
    for (const auto& pair : chunks) {
        std::cout << "Chunk at key: " << pair.first << std::endl;
    }

}

void chunkManager::update(sf::RenderWindow &window, sf::View &view, sf::Time deltaTime){
  render(window);
  
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
    view.move(0, -moveSpeed * deltaTime.asSeconds());
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
    view.move(-moveSpeed * deltaTime.asSeconds(), 0);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
    view.move(0, moveSpeed * deltaTime.asSeconds());
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
    view.move(moveSpeed * deltaTime.asSeconds(), 0);
  }
  
  //prints mouse pos to top left for debugging
  std::ostringstream oss;
  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  oss << "Mouse Position: (" << mousePos.x << ", " << mousePos.y << ")";
  text.setString(oss.str());
  sf::Vector2f viewTopLeft = window.mapPixelToCoords(sf::Vector2i(0, 0));
  text.setPosition(viewTopLeft.x + 10, viewTopLeft.y + 10);

  window.draw(text);
  window.setView(view);
}

void chunkManager::render(sf::RenderWindow &window){
  for (auto &pair : chunks) {
    window.draw(*pair.second);
  }
}

