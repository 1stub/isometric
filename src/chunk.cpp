#include "chunk.h"
#include "constants.h"

Chunk::Chunk(){
  if(!b_texture.loadFromFile("../img/grass.png")){
    std::cout << "couldnt load tile" << std::endl;
  }
  //tile size / 2 here accounts for the offset occuring when we rotate the map for the iso projection
  screenCenter = sf::Vector2f(Game::screenWidth/2.0f - Chunks::tileSize/2.0f, 
                              Game::screenHeight/2.0f - Chunks::tileSize/2.0f);
  c_blocks.setPrimitiveType(sf::Quads);
}

// for the entire 16x16x32 space I am working in this creates a value of -1 or 1 to determine whether the block exists here. Used in marching cubes algorithm.
// the reason we have the -1 for starting values and x+1, y+1 in the assignment is due to the consideration of blocks just outside of the chunk.
// this removes the need to fetch adjacent chunks but still allows for proper check to determien what block to render
void Chunk::generateVoxelGrid(sf::Vector2i coords, const siv::PerlinNoise &p, int octaves, float persistence){
  for(int x = -1; x < Chunks::size + 1; ++x){
    for(int y = -1; y < Chunks::size + 1; ++y){
      double noiseValue = p.normalizedOctave2D_01(((coords.x + x) * 0.01), ((coords.y + y) * 0.01), octaves, persistence);
      int height = static_cast<int>(noiseValue * 10);
      //std::cout << height << std::endl;

      for(int z = 0; z < Chunks::maxHeight; ++z){
        voxelGrid[x+1][y+1][z] = (z < height) ? 1 : -1;
      }
    }
  }
}

// we look into our grid and run necessary checks to determine whether the block is exposed
bool Chunk::isExposed(int x, int y, int z){
  if (voxelGrid[x+1][y+1][z] <= 0) return false;

  //I dont think all of these checks are necessary, leaving for now though
  // Check neighbors in the expanded grid
  if (voxelGrid[x][y + 1][z] <= 0) return true; // left
  if (voxelGrid[x + 2][y + 1][z] <= 0) return true; // right
  if (voxelGrid[x + 1][y][z] <= 0) return true; // top
  if (voxelGrid[x + 1][y + 2][z] <= 0) return true; // bottom
  if (z > 0 && voxelGrid[x + 1][y + 1][z - 1] <= 0) return true; // front
  if (z < Chunks::maxHeight - 1 && voxelGrid[x + 1][y + 1][z + 1] <= 0) return true; // back


  return false;
}

// the idea here is to go through each value created in the voxelGrid and see if it is exposed
// if it is exposed then we will need to draw it since the player can see it.
// so we would just create all the verticies necessary and apply textures to make it visibile
// pushing into the c_blocks buffer to be draw later
void Chunk::setVisibleBlocks(sf::Vector2i coords, const siv::PerlinNoise& p, int octaves, float persistence){
  generateVoxelGrid(coords, p, octaves, persistence);
  for(int x = 0; x < Chunks::size; ++x){
    for(int y = 0; y < Chunks::size; ++y){
      for(int z = 0; z < Chunks::maxHeight; z++){
        if(isExposed(x, y, z)){
          sf::Vertex quad[4];
          
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

          //populates c_verticies with all verticies in the column to be eventually rendered from c_blocks.
          //Should be more efficient than sf::VertexArray since we have access to gpu to render blocks now
          for(int i = 0; i < 4; i++){
            c_vertices.push_back(quad[i]);
          }
        } 
      }
    }
  }
  c_blocks.create(c_vertices.size());
  c_blocks.update(c_vertices.data());
}

sf::Vector2f Chunk::toIso(float x, float y) {
    return sf::Vector2f((x - y) * (Chunks::tileSize / 2.0f), (x + y) * (Chunks::tileSize / 4.0f));
}

