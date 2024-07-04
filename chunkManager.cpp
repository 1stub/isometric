#include "chunkManager.h"

void chunkManager::render(sf::RenderWindow& window){
  for(auto& chunk : chunks){
    chunk.second.updateAndDraw(window);
  }
}

Chunk chunkManager::createChunk(sf::Vector2i coords){
  auto chunk = Chunk(16, 16);
  return chunk;
}
