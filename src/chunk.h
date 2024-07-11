#ifndef CHUNK_H
#define CHUNK_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "constants.h"
#include "perlin.hpp"

class Chunk : public sf::Transformable, public sf::Drawable{
  public:
    Chunk();
    void setBlocks(sf::Vector2i coords, const siv::PerlinNoise& p);
    sf::Vector2f toIso(float x, float y);
  private:
    sf::Vector2f screenCenter;
    sf::Texture b_texture;
    std::vector<sf::VertexArray> c_blocks; //contains verticies for each block in chunk

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
      states.transform *= getTransform();
      states.texture = &b_texture;
      for(const auto &block : c_blocks){
          target.draw(block, states);
      }
    }
};

#endif
