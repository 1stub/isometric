#include <SFML/Graphics.hpp>
#include <iostream>
#include <unordered_map>
#include "chunk.h"

class chunkManager{
  public:
    void render(sf::RenderWindow& window);
    Chunk createChunk(sf::Vector2i coords);
  private:
    std::unordered_map<std::string, Chunk> chunks;
};
