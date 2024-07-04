#include "chunk.h"

Chunk::Chunk(int w, int h, int tileSize) : Map(w,h, tileSize){
}

void Chunk::initChunk(Perlin &p, int xCoord, int yCoord){ //this creates the chunk
  x = xCoord;
  y = yCoord;
  setTile(0, 0, xCoord, yCoord, p, SCREEN_WIDTH, SCREEN_HEIGHT, chunkSize);
}

sf::Vector2i Chunk::getCoords(){
  sf::Vector2i coords = sf::Vector2i(x,y);
  return coords; 
}
