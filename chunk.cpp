#include "chunk.h"
#include <iostream>

Chunk::Chunk(int c) : chunkSize(c){
  if(!c_texture.loadFromFile("grass.png")){
    std::cout << "couldnt load tile" << std::endl;
  }
  c_vertices.setPrimitiveType(sf::Quads);
  c_vertices.resize(c * c * 4); //16x16 each verticie has 4 points                              
  screenCenter = sf::Vector2f(SCREEN_WIDTH/2 - 16, SCREEN_HEIGHT/2 - 16);
}

void Chunk::setBlocks(int x, int y, Perlin &p){
  for(int i = 0; i < chunkSize; ++i){
    for(int j = 0; j < chunkSize; ++j){
      double noiseValue = p.noise((double)(x+i) * 0.05, (double)(y+j) * 0.05, 1, 2, 0.5);
      coords.push_back({x+i, y+j, (int)noiseValue});

      sf::Vertex* quad = &c_vertices[((i) + (j) * chunkSize) * 4];

      sf::Vector2f pos = toIso(x + i, y + j) + (sf::Vector2f(screenCenter.x*4, screenCenter.y * 4  - toIso(64,64).y));
      // Set the positions of the 4 corners of the quad in isometric space
      quad[0].position = pos;
      quad[1].position = sf::Vector2f(pos.x + c_tileSize, pos.y);
      quad[2].position = sf::Vector2f(pos.x + c_tileSize, pos.y + c_tileSize);
      quad[3].position = sf::Vector2f(pos.x, pos.y + c_tileSize);

      // Set the texture coordinates (assuming the whole texture is used for each tile)
      quad[0].texCoords = sf::Vector2f(0, 0);
      quad[1].texCoords = sf::Vector2f(c_tileSize, 0);
      quad[2].texCoords = sf::Vector2f(c_tileSize, c_tileSize);
      quad[3].texCoords = sf::Vector2f(0, c_tileSize);
    } 
  }
}

sf::Vector2f Chunk::toIso(float x, float y) {
    return sf::Vector2f((x - y) * (c_tileSize / 2.0f), (x + y) * (c_tileSize / 4.0f));

}
