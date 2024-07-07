#include "chunk.h"
#include <iostream>

class chunkManager{
  public:
    chunkManager(Perlin &perlin);
    void update(sf::RenderWindow &window, sf::View &view,  sf::Time deltaTime);
    void render(sf::RenderWindow &window);
    sf::Vector2i toCartesian(sf::Vector2i isoCoords);
  private:
    const float moveSpeed = 200.0f; // pixels per second
    sf::Vector2f screenCenter;
    std::vector<Chunk> chunks;
    Perlin &p;

    const float SCREEN_WIDTH = 1600;
    const float SCREEN_HEIGHT = 900;

    //FOR DEBUGGING
    sf::Text text;
    sf::Font font;
};
