#include "chunkManager.h"
#include <SFML/System/Vector2.hpp>

// For each chunk in chunks array, take the "player" position, if the distance from player to chunk is less than render distance render the chunk
chunkManager::chunkManager(Perlin &p) : chunkSize(16), noise(p) {

}

void chunkManager::render(sf::RenderWindow& window){
  for(auto& chunk : chunks){
    chunk.second->updateAndDraw(window);
  }
}

void chunkManager::update(sf::RenderWindow &window){
  if(!good){
    for(int i = 0; i < 128; i+=16){
      for(int j = 0; j < 128; j+=16){
        sf::Vector2i coords(i,j);
        std::string stringCoords = std::to_string(i) + "," + std::to_string(j);
        chunks[stringCoords] = createChunk(coords);
      }
    }
    good = true;
  }
  render(window);
}

std::unique_ptr<Chunk> chunkManager::createChunk(sf::Vector2i coords){
  auto chunk = std::make_unique<Chunk>(16,16); //creates the chunk object we need
  chunk->initChunk(noise, coords.x, coords.y);
  return chunk;
}

