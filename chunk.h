#ifndef CHUNK_H
#define CHUNK_H

#include <SFML/Graphics.hpp>
#include "perlin.h"

class Chunk : public sf::Transformable, public sf::Drawable{
  public:
    Chunk(int c);
    void setBlocks(int x, int y,  Perlin &p); //sets all blocks in chunk object
  private:
    sf::Vector2f toIso(float x, float y); 

    struct Point3D {
      int x;
      int y;
      int z;
    };

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();
        states.texture = &c_texture;
        target.draw(c_vertices, states);
    }

    const float SCREEN_WIDTH = 1600;
    const float SCREEN_HEIGHT = 900;
    int chunkSize;

    sf::Vector2f screenCenter;
    std::vector<Point3D> coords; // this is specifically used for noise
    sf::VertexArray c_vertices;
    sf::Texture c_texture;
    float c_tileSize = 32; //32 pixels in one tile
};

#endif
