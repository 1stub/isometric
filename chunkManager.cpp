#include "chunkManager.h"

void chunkManager::update(Perlin &p){
  for(int i = 0; i < 128; i++){
    for(int j = 0; j < 128; j++){
      auto chunk = Chunk(16);
      chunk.setBlocks(i,j,p);
      chunk.scale(0.25f, 0.25f);
      chunks.push_back(chunk);
    }
  }
}

void chunkManager::render(sf::RenderWindow &window){
  for(auto &chunk : chunks){
    window.draw(chunk);
  }
}
