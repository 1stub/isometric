#ifndef CHUNK_H
#define CHUNK_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"
#include "perlin.hpp"

class Chunk : public sf::Transformable, public sf::Drawable{
  public:
    Chunk();
    void setBlocks(sf::Vector2i coords, const siv::PerlinNoise& p, int octaves, int frequency);
    sf::Vector2f toIso(float x, float y);
  private:
    sf::Vector2f screenCenter;
    sf::Texture b_texture;

    //convert to vertex buffer for better performance - allows conversation (lol) with gpu for rendering blocks
    sf::VertexBuffer c_blocks; //contains verticies for each block in chunk
    std::vector<sf::Vertex> c_vertices;

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
      states.transform *= getTransform();
      states.texture = &b_texture;
      target.draw(c_blocks, states);
    }
};

#endif
