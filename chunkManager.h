#include "chunk.h"
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>

class chunkManager{
  public:
    chunkManager(const siv::PerlinNoise &perlin);
    void update(sf::RenderWindow &window, sf::View &view,  sf::Time deltaTime);
    void render(sf::RenderWindow &window);
    void loadChunks();
    sf::Vector2i toCartesian(sf::Vector2i isoCoords);
  private:
    const int renderLimit = 3; //max 3 surrounding chunks from player
    const float moveSpeed = 200.0f; // pixels per second
    sf::Vector2f screenCenter;
    std::vector<std::pair<std::string, std::shared_ptr<Chunk>>> chunks; //had to use a vector to avoid hashing issues
    const siv::PerlinNoise &p;

    const float SCREEN_WIDTH = 1600;
    const float SCREEN_HEIGHT = 900;

    //FOR DEBUGGING
    sf::Text text;
    sf::Font font;
};
