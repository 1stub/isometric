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
  screenCenter = sf::Vector2f(SCREEN_WIDTH/2 - 16, SCREEN_HEIGHT/2 - 16);
  for(int i = 0; i < 128; i+=16){
    for(int j = 0; j < 128; j+=16){
      auto chunk = Chunk(16);
      chunk.setBlocks(i,j,p);
      chunk.scale(0.25f, 0.25f);
      chunks.push_back(chunk);
    }
  }

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
    const float renderDistanceSquared = 512 * 512;

    for (auto &chunk : chunks) {
        sf::Vector2f chunkScreenCoord = chunk.getScreenCoords();
        float a = chunkScreenCoord.x - screenCenter.x;
        float b = chunkScreenCoord.y - screenCenter.y;
        float distSquared = a * a + b * b;

        if (distSquared < renderDistanceSquared) {
          window.draw(chunk);
        }
    }
}

