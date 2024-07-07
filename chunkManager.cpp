#include "chunkManager.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <sstream>
#include <cmath>
#include <utility>

const float i_x = 1;
const float i_y = 0.5;
const float j_x = -1;
const float j_y = 0.5;

const int w = 32;
const int h = 32;

chunkManager::chunkManager(Perlin &perlin) : p(perlin){
  for(int i = 0; i < 128; i+=16){
    for(int j = 0; j < 128; j+=16){
      auto chunk = Chunk(16);
      chunk.setBlocks(i,j,p);
      chunk.scale(0.25f, 0.25f);
      chunks.push_back(chunk);
      std::cout << isoToScreen(chunk.getCoords()).x << std::endl;
    }
  }
  screenCenter = sf::Vector2i(1600/2 , 900/2);

  if (!font.loadFromFile("Eight-Bit Madness.ttf")) {
    std::cout << "font err" << std::endl;
  }
  text.setFont(font);
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);
  text.setPosition(10, 10);
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
 
  std::ostringstream oss;
  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  oss << "Mouse Position: (" << mousePos.x << ", " << mousePos.y << ")";
  text.setString(oss.str());
  sf::Vector2f viewTopLeft = window.mapPixelToCoords(sf::Vector2i(0, 0));
  text.setPosition(viewTopLeft.x + 10, viewTopLeft.y + 10);

  window.draw(text);
  window.setView(view);
}

sf::Vector2f chunkManager::isoToScreen(sf::Vector2i coord){ //converts game coords to px
  return sf::Vector2f(coord.x * i_x * 0.5 * w + coord.y * j_x * 0.5 * w,
                      coord.x * i_y * 0.5 * h + coord.y * j_y * 0.5 * h);
}

void chunkManager::render(sf::RenderWindow &window){
    /*const float renderDistanceSquared = 1024 * 1024;

    for (auto &chunk : chunks) {
        sf::Vector2f chunkScreenCoord = isoToScreen(chunk.getCoords());
        float a = chunkScreenCoord.x - screenCenter.x;
        float b = chunkScreenCoord.y - screenCenter.y;
        float distSquared = a * a + b * b;

        if (distSquared < renderDistanceSquared) {
          window.draw(chunk);
        }
    }*/
  for(auto &chunk : chunks){
    if(chunk.isLoaded()){
      window.draw(chunk);
    }
  }
}

