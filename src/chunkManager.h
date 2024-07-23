#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <thread>
#include <future>
#include <mutex>
#include <vector>
#include <unordered_map>

#include "chunk.h"

class chunkManager{
  public:
    chunkManager(const siv::PerlinNoise &p, sf::RenderWindow &w, sf::View &view, int octaves, float per, float newFreq); 
    void update(int newOct, float newPer, float newFreq);
    void updateChunks();
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
    std::map<std::pair<int,int>, Chunk> chunkToLoad; //used threads
    std::vector<std::future<Chunk>> futures;
    int octaves;
    float frequency;
    float persistence;
};

#endif
