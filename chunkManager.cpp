#include "chunkManager.h"
#include <SFML/System/Vector2.hpp>
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
    }
  }
  screenCenter = sf::Vector2i(1600/2 , 900/2);
}

void chunkManager::update(sf::RenderWindow &window){
  render(window);
}

sf::Vector2f isoToScreen(sf::Vector2i coord){ //converts game coords to px
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

