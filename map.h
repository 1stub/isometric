#include <SFML/Graphics.hpp>

class Map : public sf::Drawable, public sf::Transformable{
  public:
    Map(int w, int h, int tileSize = 32);
    void loadTileset(const std::string& tilesetPath);
    void setTile(int x, int y, int tileNumber, float screenWidth, float screenHeight, int mapWidth, sf::Vector2i mousePos);
    int getTile(int x, int y) const;
    void transformTile(int x, int y, const sf::Transform& transform);
    sf::Vector2f toIso(float x, float y);
    void moveMap(Map &map);
    void updateAndDraw(sf::RenderTarget& target);
  private:
    int width;
    int height;
    int tileSize;
    
    sf::Vector2i mousePos;
    std::vector<std::vector<int>> tiles;
    sf::VertexArray vertices;            // Vertex array for rendering
    sf::Texture tileset;                 // Texture for the tiles

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
