#ifndef CHUNK_H
#define CHUNK_H

#include "../include/imgui/imgui.h" //attached imgui here just so its visible across main files
#include "../include/imgui/imgui-SFML.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"
#include "perlin.hpp"

class Chunk : public sf::Transformable, public sf::Drawable{
  public:
    Chunk();
    void generateVoxelGrid(sf::Vector2i coords, const siv::PerlinNoise &p, int octaves, float persistence, int frequency);
    bool isExposed(int x, int y, int z);
    void setVisibleBlocks(sf::Vector2i coords, const siv::PerlinNoise& p, int octaves, float persistence, int frequency);
    sf::Vector2f toIso(float x, float y);
  private:
    sf::Vector2f screenCenter;
    sf::Texture b_texture;

    //convert to vertex buffer for better performance - allows conversation (lol) with gpu for rendering blocks
    sf::VertexBuffer c_blocks; //contains verticies for each block in chunk
    std::vector<sf::Vertex> c_vertices;
    int voxelGrid[Chunks::size + 2][Chunks::size + 2][Chunks::maxHeight];
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
      states.transform *= getTransform();
      states.texture = &b_texture;
      target.draw(c_blocks, states);
    }
};

#endif
