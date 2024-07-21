#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <thread>
#include <mutex>
#include <vector>

#include "chunk.h"

class chunkManager{
  public:
    chunkManager(const siv::PerlinNoise &p, sf::RenderWindow &w, sf::View &view, int octaves, float per, float newFreq); 
    void update(int newOct, float newPer, float newFreq);
    void updateNoise();
    void loadChunk(int chunkX, int chunkY, bool update);
    void unloadChunk();
    void renderChunks(bool update);
  private:
    const siv::PerlinNoise &perlin;
    sf::RenderWindow &window;
    sf::View &view;
    sf::Vector2i chunkPosition;
    sf::Vector2f screenCenter;
    std::map<std::pair<int,int>, Chunk> chunks;
    int octaves;
    float frequency;
    float persistence;
};

#endif
