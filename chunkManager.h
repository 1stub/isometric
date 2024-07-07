#include "chunk.h"
#include <iostream>

class chunkManager{
  public:
    chunkManager(Perlin &perlin);
    void update(sf::RenderWindow &window, sf::View &view,  sf::Time deltaTime);
    void render(sf::RenderWindow &window);
  private:
    const float moveSpeed = 200.0f; // pixels per second
    sf::Vector2i screenCenter;
    std::vector<Chunk> chunks;
    Perlin &p;
};
