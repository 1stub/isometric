#include <SFML/Graphics.hpp>

class Map : public sf::Drawable, public sf::Transformable{
  public:
    Map(int w, int h, int tileSize = 32);
    void loadTileset(const std::string& tilesetPath);
    void setTile(int x, int y, int tileNumber);
    int getTile(int x, int y) const;
    void transformTile(int x, int y, const sf::Transform& transform);
    sf::Vector2f toIso(float x, float y);
  private:
    int width;
    int height;
    int tileSize;
    
    std::vector<std::vector<int>> tiles;
    sf::VertexArray vertices;            // Vertex array for rendering
    sf::Texture tileset;                 // Texture for the tiles

    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
};
