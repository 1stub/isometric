#include "chunk.h"
#include <iostream>

class chunkManager{
  public:
    chunkManager(Perlin &perlin);
    void update(sf::RenderWindow &window);
    void render(sf::RenderWindow &window);
  private:

    sf::Vector2i screenCenter;
    std::vector<Chunk> chunks;
    Perlin &p;
};
