#ifndef MAP_H
#define MAP_H

#include <SFML/Graphics.hpp>
#include "perlin.h"

class Map : public sf::Drawable, public sf::Transformable{
  public:
    Map(int w, int h, int tileSize = 32);
    void loadTileset(const std::string& tilesetPath);
    void setTile(int x, int y, int xCoord, int yCoord ,Perlin &p, float screenWidth, float screenHeight, int mapWidth);
    void moveTile(int x, int y);
    int getTile(int x, int y) const;
    void transformTile(int x, int y, const sf::Transform& transform);
    sf::Vector2f toIso(float x, float y);
    void updateAndDraw(sf::RenderTarget& target);
  private:
    const float SCREEN_WIDTH = 1600;
    const float SCREEN_HEIGHT = 900;
    int width;
    int height;
    int tileSize;
    bool isDragging = false;
   
    sf::Vector2f mapCenter;
    sf::Vector2f screenCenter;
    sf::Vector2f offset;
    sf::Vector2i mousePos;
    sf::Vector2i initialMousePos;
    sf::Vector2i previousMousePos;
    std::vector<std::vector<int>> tiles;
    sf::VertexArray vertices;            // Vertex array for rendering
    sf::Texture tileset;                 // Texture for the tiles

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};

#endif
