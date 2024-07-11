#include "chunk.h"
#include "constants.h"

Chunk::Chunk(){
  if(!b_texture.loadFromFile("../img/grass.png")){
    std::cout << "couldnt load tile" << std::endl;
  }
  //tile size / 2 here accounts for the offset occuring when we rotate the map for the iso projection
  screenCenter = sf::Vector2f(Game::screenWidth/2.0f - Chunks::tileSize/2.0f, 
                              Game::screenHeight/2.0f - Chunks::tileSize/2.0f);
}

void Chunk::setBlocks(sf::Vector2i coords, const siv::PerlinNoise& p){
  for(int x = 0; x < Chunks::size; ++x){
    for(int y = 0; y < Chunks::size; ++y){
      double noiseValue = p.octave2D_01(((coords.x + x) * 0.01), ((coords.y + y) * 0.01), 4);
      int height = static_cast<int>(noiseValue * 10); //represents height of column
      
      sf::VertexArray column(sf::Quads, height * 4);
      for(int z = 0; z < height; ++z){
        sf::Vertex* quad = &column[z*4];
        
        //Creates the isometric position in px for each coordinate in our map, then sets an offset for each block in height
        sf::Vector2f pos = toIso(coords.x + x, coords.y + y)
                          + screenCenter - sf::Vector2f(0, z*(Chunks::tileSize/2.0f));
        
        // Set the positions of the 4 corners of the quad in isometric space
        quad[0].position = pos;
        quad[1].position = sf::Vector2f(pos.x + Chunks::tileSize, pos.y);
        quad[2].position = sf::Vector2f(pos.x + Chunks::tileSize, pos.y + Chunks::tileSize);
        quad[3].position = sf::Vector2f(pos.x, pos.y + Chunks::tileSize);

        quad[0].texCoords = sf::Vector2f(0, 0);
        quad[1].texCoords = sf::Vector2f(Chunks::tileSize, 0);
        quad[2].texCoords = sf::Vector2f(Chunks::tileSize, Chunks::tileSize);
        quad[3].texCoords = sf::Vector2f(0, Chunks::tileSize);     
      }
      c_blocks.push_back(column);
    }
  }
}

sf::Vector2f Chunk::toIso(float x, float y) {
    return sf::Vector2f((x - y) * (Chunks::tileSize / 2.0f), (x + y) * (Chunks::tileSize / 4.0f));
}
