#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include "chunk.h"

class chunkManager{
  public:
    chunkManager(const siv::PerlinNoise &p, sf::RenderWindow &w, sf::View &view, int octaves, float per);
    void update(int newOct, float newPer);
    void updateNoise();
    void loadChunk(int chunkX, int chunkY, bool update);
    void unloadChunk();
    void renderChunks();
  private:
    const siv::PerlinNoise &perlin;
    sf::RenderWindow &window;
    sf::View &view;
    sf::Vector2i chunkPosition;
    sf::Vector2f screenCenter;
    std::map<std::pair<int,int>, Chunk> chunks;
    int octaves;
    float persistence;
};

#endif
