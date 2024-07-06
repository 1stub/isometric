#include "chunk.h"
#include <iostream>

class chunkManager{
  public:
    void update(Perlin &p);
    void render(sf::RenderWindow &window);
  private:
    std::vector<Chunk> chunks;
};
