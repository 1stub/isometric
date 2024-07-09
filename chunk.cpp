#include "chunk.h"
#include <iostream>

Chunk::Chunk(int c) : chunkSize(c){
  if(!c_texture.loadFromFile("grass.png")){
    std::cout << "couldnt load tile" << std::endl;
  }
  screenCenter = sf::Vector2f(SCREEN_WIDTH/2 - 16, SCREEN_HEIGHT/2 - 16);
  loaded = true;
}

bool Chunk::isLoaded(){
  return loaded;
}

void Chunk::setBlocks(int x, int y, const siv::PerlinNoise& p){
  c_x = x;
  c_y = y;

  //records block 0,0 in this chunks screen coords, divided by 4 here due to scale of 0.25 in chunk manager. Need to create global variables to help fix some of these magic numbers 
  chunkStartingPos = (toIso(x,y) + (sf::Vector2f(screenCenter.x*4, screenCenter.y * 4  - toIso(64,64).y)))/4.0f;
  for(int i = 0; i < chunkSize; ++i){
    for(int j = 0; j < chunkSize; ++j){
      double noiseValue = p.octave2D_01(((x + i) * 0.01), ((y + j) * 0.01), 4);
      double height  = (noiseValue * 10);
     
      //std::cout << (int)height << std::endl;
      coords.push_back({x+i, y+j, (int)height}); 
      sf::VertexArray column(sf::Quads, (int)height * 4); 
      
      for(int k = 0; k < (int)height; ++k){
        sf::Vertex* quad = &column[k*4];
        sf::Vector2f pos = toIso(x + i, y + j) + (sf::Vector2f(screenCenter.x*4, screenCenter.y * 4)) - sf::Vector2f(0, k*(c_tileSize/2));
        // Set the positions of the 4 corners of the quad in isometric space
        quad[0].position = pos;
        quad[1].position = sf::Vector2f(pos.x + c_tileSize, pos.y);
        quad[2].position = sf::Vector2f(pos.x + c_tileSize, pos.y + c_tileSize);
        quad[3].position = sf::Vector2f(pos.x, pos.y + c_tileSize);

        quad[0].texCoords = sf::Vector2f(0, 0);
        quad[1].texCoords = sf::Vector2f(c_tileSize, 0);
        quad[2].texCoords = sf::Vector2f(c_tileSize, c_tileSize);
        quad[3].texCoords = sf::Vector2f(0, c_tileSize);

        /*std::cout << "Block at (" << x + i << ", " << y + j << ") -> Screen Pos: (" << pos.x << ", " << pos.y << ")" << std::endl;*/
      }
      blocks.push_back(column);
    }
    //std::cout << chunkStartingPos.x << " " << chunkStartingPos.y << std::endl;
  }
}

bool Chunk::containsPlayer(sf::Vector2i player){
    sf::Vector2f bottomLeftBound = sf::Vector2f(chunkStartingPos.x, chunkStartingPos.y - 16);
    sf::Vector2f bottomRightBound = sf::Vector2f(chunkStartingPos.x + 16, chunkStartingPos.y - 16);
    sf::Vector2f topLeftBound = chunkStartingPos;
    sf::Vector2f topRightBound = sf::Vector2f(chunkStartingPos.x + 16, chunkStartingPos.y);

    return (player.x >= topLeftBound.x && player.x <= topRightBound.x && player.y <= bottomLeftBound.y && player.y >= topLeftBound.y);
}

sf::Vector2f Chunk::toIso(float x, float y) {
    return sf::Vector2f((x - y) * (c_tileSize / 2.0f), (x + y) * (c_tileSize / 4.0f));
}

sf::Vector2i Chunk::getCoords(){
  return sf::Vector2i(c_x,c_y);
}

sf::Vector2f Chunk::getScreenCoords(){
  return chunkStartingPos;
}
