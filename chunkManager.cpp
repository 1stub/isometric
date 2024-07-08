#include "chunkManager.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <sstream>
#include <string>

const int w = 32;
const int h = 32;

chunkManager::chunkManager(const siv::PerlinNoise &perlin) : p(perlin){
  screenCenter = sf::Vector2f(SCREEN_WIDTH/2 - 16, SCREEN_HEIGHT/2 - 16);
  playerPosition = sf::Vector2i(0,0);
  if (!font.loadFromFile("Eight-Bit Madness.ttf")) {
    std::cout << "font err" << std::endl;
  }
  text.setFont(font);
  text.setCharacterSize(24);
  text.setFillColor(sf::Color::White);
  text.setPosition(10, 10);

}

void chunkManager::loadChunks(sf::Vector2i offset){
    for (int i = offset.x - renderLimit; i < offset.x + renderLimit; ++i) {
        for (int j = offset.y - renderLimit; j < offset.y + renderLimit; ++j) {

            // Check if the chunk already exists
            bool chunkExists = false;
            for (auto chunk = chunks.begin(); chunk != chunks.end(); chunk++) {
              if(std::abs(offset.x - chunk->first.first) > renderLimit ||std::abs(offset.y - chunk->first.second) > renderLimit){
                chunks.erase(chunk);
              }
              if (chunk->first == std::pair(i,j)) {
                  chunkExists = true;
                  break;
              }
            }

            // If the chunk does not exist, create and add it
            if (!chunkExists) {
                auto chunk = std::make_shared<Chunk>(16);
                chunk->setBlocks(i * 16 + offset.x, j * 16 + offset.y, p);
                chunk->scale(0.25f, 0.25f);
                chunks.push_back({std::pair(i,j), chunk});
            }
        }
    }

}

void chunkManager::update(sf::RenderWindow &window, sf::View &view, sf::Time deltaTime){
  int chunkX = playerPosition.x/16;
  int chunkY = playerPosition.y/16;
 
  loadChunks(sf::Vector2i(chunkX, chunkY));

  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
    playerPosition.y += -1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
    playerPosition.x += -1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
    playerPosition.y += 1;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
    playerPosition.x += 1;
  }
 
  view.setCenter(sf::Vector2f(playerPosition.x, playerPosition.y) + screenCenter);

  std::cout << playerPosition.x << ", " << playerPosition.y << std::endl;

  //prints mouse pos to top left for debugging
  std::ostringstream oss;
  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  oss << "Mouse Position: (" << mousePos.x << ", " << mousePos.y << ")";
  text.setString(oss.str());
  sf::Vector2f viewTopLeft = window.mapPixelToCoords(sf::Vector2i(0, 0));
  text.setPosition(viewTopLeft.x + 10, viewTopLeft.y + 10);

  window.draw(text);
  window.setView(view);

  render(window);
}

void chunkManager::render(sf::RenderWindow &window){
  //std::sort(chunks.begin(), chunks.end());

  for (auto &pair : chunks) { 
      window.draw(*pair.second);
  }
}

