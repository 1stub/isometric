#ifndef CHUNKMANAGER_H
#define CHUNKMANAGER_H

#include <iostream>
#include <memory>
#include <unordered_map>
#include "chunk.h"

//Likely would be smarter (and more memory efficient due to large number of blocks being rendered)
//to store the chunks as smart pointers so that when they get out of scope their memory becomes deallocated
//I can do this like so 
//std::unique_ptr<Chunk> chunk = std::make_unique<Chunk>();
//these pointers CANNOT be copied into other entities. Could need to convert to shared_ptr but unlikely

class chunkManager{
  public:
    chunkManager(Perlin &p);
    void render(sf::RenderWindow& window);
    void update(sf::RenderWindow &window);
  
  private:
    std::unique_ptr<Chunk> createChunk(sf::Vector2i coords);
    std::unordered_map<std::string, std::unique_ptr<Chunk>> chunks;
    bool good = false;
    int chunkSize;
    Perlin &noise; //for terrain gen
};

#endif
