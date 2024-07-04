#include "chunkManager.h"
#include <SFML/System/Vector2.hpp>

chunkManager::chunkManager(Perlin &p) : chunkSize(16), noise(p) {

}

void chunkManager::render(sf::RenderWindow& window){
  for(auto& chunk : chunks){
    chunk.second->updateAndDraw(window);
  }
}

void chunkManager::update(sf::RenderWindow &window){
  if(!good){
    std::string coord = "0,0";
    sf::Vector2i coords(0,0);
    chunks[coord] = createChunk(coords);
    good = true;
  }
  render(window);
}

std::unique_ptr<Chunk> chunkManager::createChunk(sf::Vector2i coords){
  auto chunk = std::make_unique<Chunk>(16,16); //creates the chunk object we need
  chunk->initChunk(noise, coords.x, coords.y);
  return chunk;
}

