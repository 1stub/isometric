#ifndef CHUNK_H
#define CHUNK_H

#include <SFML/Graphics.hpp>
#include "map.h"


class Chunk : public Map{
  public:
    Chunk(int w, int h, int tileSize = 32);
    void initChunk(Perlin &p, int xCoord, int yCoord);
    sf::Vector2i getCoords();
  private:
    int x, y;
    int chunkSize = 16;
    const float SCREEN_WIDTH = 1600;
    const float SCREEN_HEIGHT = 900;
};

#endif
