#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include "chunk.h"

class chunkManager{
  public:
    chunkManager(const siv::PerlinNoise &p, sf::RenderWindow &w, sf::View &view);
    void update();
    void loadChunk(int chunkX, int chunkY);
    void unloadChunk();
    void renderChunks();
  private:
    const siv::PerlinNoise &perlin;
    sf::RenderWindow &window;
    sf::View &view;
    sf::Vector2i chunkPosition;
    sf::Vector2f screenCenter;
    std::map<std::pair<int,int>, Chunk> chunks;

};

#endif
