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

void Map::setTile(int x, int y, int tileNumber) {
    tiles[x][y] = tileNumber;

    sf::Vertex* quad = &vertices[(x + y * width) * 4];

    int tu = 0;
    int tv = 0;

    quad[0].position = sf::Vector2f(x * tileSize, y * tileSize);
    quad[1].position = sf::Vector2f((x + 1) * tileSize, y * tileSize);
    quad[2].position = sf::Vector2f((x + 1) * tileSize, (y + 1) * tileSize);
    quad[3].position = sf::Vector2f(x * tileSize, (y + 1) * tileSize);

    quad[0].texCoords = sf::Vector2f(tu, tv);
    quad[1].texCoords = sf::Vector2f(tu + tileSize, tv);
    quad[2].texCoords = sf::Vector2f(tu + tileSize, tv + tileSize);
    quad[3].texCoords = sf::Vector2f(tu, tv + tileSize);
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
    return sf::Vector2f(x + y, (y - x) / 2);
}

void Map::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &tileset;
    target.draw(vertices, states);
}
