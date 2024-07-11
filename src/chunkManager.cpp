#include "chunkManager.h"
#include "constants.h"

sf::Vector2f toIso(float x, float y) {
    return sf::Vector2f((x - y) * (Chunks::tileSize / 2.0f), (x + y) * (Chunks::tileSize / 4.0f));
}

chunkManager::chunkManager(const siv::PerlinNoise &p, sf::RenderWindow &w, sf::View &v) : perlin(p), window(w), view(v){
  chunkPosition = sf::Vector2i(0,0);
  loadChunk(chunkPosition.x, chunkPosition.y);
  screenCenter = sf::Vector2f(Game::screenWidth/2.0f - Chunks::tileSize/2.0f, 
                              Game::screenHeight/2.0f - Chunks::tileSize/2.0f);
}

void chunkManager::update(){ 
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
    chunkPosition.y -= 1;
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
    chunkPosition.x -= 1;
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
    chunkPosition.y += 1;
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
    chunkPosition.x += 1;
  }

  sf::Vector2f playerIsoPosition = toIso(static_cast<float>(chunkPosition.x) * Chunks::size, static_cast<float>(chunkPosition.y) * Chunks::size);
  view.setCenter(
     playerIsoPosition.x + screenCenter.x, playerIsoPosition.y + screenCenter.y
  );
  window.setView(view);

  renderChunks();
}

//we see if a chunk corresponding to this coord exists (in chunk coords not game), if it does just load, otherwise create and load
void chunkManager::loadChunk(int chunkX, int chunkY){  
  sf::Vector2i blockCoords(chunkX * Chunks::size, chunkY * Chunks::size); //converted from chunk space to blocks in game space

  //chunk doesnt exist in map
  if(chunks.find({chunkX, chunkY}) == chunks.end()){ 
    auto chunk = Chunk();
    chunk.setBlocks(blockCoords, perlin);
    chunks[{blockCoords.x, blockCoords.y}] = chunk;
  }
  window.draw(chunks[{blockCoords.x, blockCoords.y}]); 
}

void chunkManager::unloadChunk(){

}

void chunkManager::renderChunks(){
  //this creates the render view for the player, so in this case it would me Manage::renderDistance chunks that the player can see.
  for(int i = -Manage::renderDistance; i < Manage::renderDistance; ++i){
    for(int j = -Manage::renderDistance; j < Manage::renderDistance; ++j){
      loadChunk(chunkPosition.x + i, chunkPosition.y + j);
    }
  }
}