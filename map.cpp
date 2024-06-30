#include "map.h"

Map::Map(int w, int h, int tSize) : width(w), height(h), tileSize(tSize) {
    tiles.resize(width, std::vector<int>(height, 0)); // Initialize tiles with 0
    vertices.setPrimitiveType(sf::Quads);
    vertices.resize(width * height * 4); // 4 vertices per tile
}

void Map::loadTileset(const std::string& tilesetPath) {
    if (!tileset.loadFromFile(tilesetPath)) {
        throw std::runtime_error("Failed to load tileset");
    }
}

void Map::setTile(int x, int y, int tileNumber, float screenWidth, float screenHeight, int mapWidth) {
    tiles[x][y] = tileNumber;

    sf::Vertex* quad = &vertices[(x + y * width) * 4];
    //need to move these elsewhere to avoid extra calculations
    sf::Vector2f screenCenter(screenWidth/2, screenHeight/2);
    sf::Vector2f mapCenter((mapWidth - 1) * tileSize / 2.0f, (mapWidth - 1) * tileSize / 2.0f);
    sf::Vector2f offset = screenCenter - mapCenter;
    //Converts our X and Y values (cooresponding to tile entry in vector) to isometric coords
    sf::Vector2f pos = toIso(x, y) + offset;
    
    // Set the positions of the 4 corners of the quad in isometric space
    quad[0].position = pos;
    quad[1].position = sf::Vector2f(pos.x + tileSize, pos.y);
    quad[2].position = sf::Vector2f(pos.x + tileSize, pos.y + tileSize);
    quad[3].position = sf::Vector2f(pos.x, pos.y + tileSize);

    // Set the texture coordinates (assuming the whole texture is used for each tile)
    quad[0].texCoords = sf::Vector2f(0, 0);
    quad[1].texCoords = sf::Vector2f(tileSize, 0);
    quad[2].texCoords = sf::Vector2f(tileSize, tileSize);
    quad[3].texCoords = sf::Vector2f(0, tileSize);
}


int Map::getTile(int x, int y) const {
    return tiles[x][y];
}

void Map::transformTile(int x, int y, const sf::Transform& transform) {
    sf::Vertex* quad = &vertices[(x + y * width) * 4];
    for (int i = 0; i < 4; ++i) {
        quad[i].position = transform.transformPoint(quad[i].position);
    }
}

sf::Vector2f Map::toIso(float x, float y) {
    return sf::Vector2f((x - y) * (tileSize / 2.0f), (x + y) * (tileSize / 4.0f));

}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &tileset;
    target.draw(vertices, states);
}
