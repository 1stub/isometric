#include "chunkManager.h"
#include <cmath>
#include <utility>

const float i_x = 1;
const float i_y = 0.5;
const float j_x = -1;
const float j_y = 0.5;

chunkManager::chunkManager(Perlin &perlin) : p(perlin){
  for(int i = 0; i < 128; i+=16){
    for(int j = 0; j < 128; j+=16){
      auto chunk = Chunk(16);
      chunk.setBlocks(i,j,p);
      chunk.scale(0.25f, 0.25f);
      chunks.push_back(chunk);
    }
  }

}

void chunkManager::update(sf::RenderWindow &window){
  render(window);
}

std::pair<std::pair<float,float>,std::pair<float,float>> invertMatrix(float a, float b, float c, float d){
  const float det = (1/(a*d - b*c));
  return std::pair<std::pair<float,float>,std::pair<float,float>>({det * d, det * -b}, {det * -c, det * a});
}

sf::Vector2f centerToGrid(){ //used to find center of screen on the grid, used for rendering chunks
  const float a = i_x * 0.5 * 32;
  const float b = j_x * 0.5 * 32;
  const float c = i_y * 0.5 * 32;
  const float d = j_y * 0.5 * 32;

  std::pair<std::pair<float, float>, std::pair<float,float>> inv = invertMatrix(a,b,c,d);

  sf::Vector2i mousePos = sf::Vector2i(1600/2, 900/2);

  return sf::Vector2f(mousePos.x * inv.first.first + mousePos.y * inv.first.second,
                      mousePos.x * inv.second.first + mousePos.y * inv.second.second  );
}

void chunkManager::render(sf::RenderWindow &window){
  for(auto &chunk : chunks){
    //float a = centerToGrid().x - chunk.getCoords().x;
    //float b = centerToGrid().y - chunk.getCoords().y;
    // abs((double)sqrt(a*a + b*b)
    window.draw(chunk);
  }
}

