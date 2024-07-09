#include "chunkManager.h"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Mouse.hpp>
#include <sstream>
#include <string>

const int w = 32;
const int h = 32;


bool sortByFirst(const std::pair<std::pair<int,int>, std::shared_ptr<Chunk>>& a,
                 const std::pair<std::pair<int,int>, std::shared_ptr<Chunk>>& b) {
    return a.first < b.first;
}

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

  loadChunks(playerPosition);
}

void chunkManager::loadChunks(sf::Vector2i offset){
  chunks.clear();
    for (int i = offset.x - renderLimit; i < offset.x + renderLimit; ++i) {
        for (int j = offset.y - renderLimit; j < offset.y + renderLimit; ++j) {

            // Check if the chunk already exists
            bool chunkExists = false;
            for (auto chunk = chunks.begin(); chunk != chunks.end(); chunk++) {

              //std::cout << "Found chunk at coordinates: (" << chunk->first.first << ", " << chunk->first.second << ")" << std::endl;
              if(std::abs(offset.x - chunk->first.first) > renderLimit ||std::abs(offset.y - chunk->first.second) > renderLimit){
                chunks.erase(chunk);
              }
              if (chunk->first == std::make_pair(i,j)) {
                  chunkExists = true;
                  break;
              }
            }

            // If the chunk does not exist, create and add it
            if (!chunkExists) {
                auto chunk = std::make_shared<Chunk>(16);
                chunk->setBlocks(i * 16 + offset.x, j * 16 + offset.y, p);
                chunk->scale(0.25f, 0.25f);
                chunks.push_back({std::make_pair(i,j), chunk});
            }
        }
    }
}

sf::Vector2i toIso(int x, int y) {
    return sf::Vector2i((x - y) * 16, (x + y) * 8);
}

void chunkManager::update(sf::RenderWindow &window, sf::View &view, sf::Time deltaTime){
  int chunkX = playerPosition.x/16;
  int chunkY = playerPosition.y/16;

  //std::cout << chunkX << " " << chunkY << std::endl;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
    playerPosition.y += -1;
    loadChunks(playerPosition);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
    playerPosition.x += -1;
    loadChunks(playerPosition);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
    playerPosition.y += 1;
    loadChunks(playerPosition);
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
    playerPosition.x += 1;
    loadChunks(playerPosition);
  }
 
  sf::Vector2i iso = toIso(playerPosition.x, playerPosition.y);
  sf::Vector2f isoPosition(iso.x * 4, iso.y * 4);
  view.setCenter(isoPosition + screenCenter);

  std::cout << "Player Position: (" << playerPosition.x << ", " << playerPosition.y << ")" << std::endl;
  std::cout << "Isometric Position: (" << iso.x << ", " << iso.y << ")" << std::endl;
  std::cout << "View Center: (" << isoPosition.x + screenCenter.x << ", " << isoPosition.y + screenCenter.y << ")" << std::endl;

  //prints mouse pos to top left for debugging
  std::ostringstream oss;
  sf::Vector2i mousePos = sf::Mouse::getPosition(window);
  oss << "Mouse Position: (" << mousePos.x << ", " << mousePos.y << ")";
  text.setString(oss.str());
  sf::Vector2f viewTopLeft = window.mapPixelToCoords(sf::Vector2i(0, 0));
  text.setPosition(viewTopLeft.x + 10, viewTopLeft.y + 10);

  window.setView(view);
  window.draw(text);

  render(window);
}

void chunkManager::render(sf::RenderWindow &window){ 
  for (auto &pair : chunks) { 
    window.draw(*pair.second);
  }
  newChunks.clear();
}

