#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <thread>
#include <mutex>

//#include "threadpool.hpp"
#include "chunk.h"

class chunkManager{
  public:
    chunkManager(const siv::PerlinNoise &p, sf::RenderWindow &w, sf::View &view, int octaves, float per, int newFreq); //, int num_threads
    void update(int newOct, float newPer, int newFreq);
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
    //ctpl::thread_pool pool;
    //std::vector<std::future<void>> futures;
    std::map<std::pair<int,int>, Chunk> chunks;
    int octaves;
    int frequency;
    float persistence;
};

#endif
