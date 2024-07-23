#include "chunkManager.h"
#include "constants.h"

static std::mutex mtx;

sf::Vector2f toIso(float x, float y) {
    return sf::Vector2f((x - y) * (Chunks::tileSize / 2.0f), (x + y) * (Chunks::tileSize / 4.0f));
}

chunkManager::chunkManager(const siv::PerlinNoise &p, sf::RenderWindow &w, sf::View &v, int oct, float per, float freq) 
  : perlin(p), window(w), view(v), octaves(oct), persistence(per), frequency(freq){
  chunkPosition = sf::Vector2i(0,0);
  screenCenter = sf::Vector2f(Game::screenWidth/2.0f - Chunks::tileSize/2.0f, 
                              Game::screenHeight/2.0f - Chunks::tileSize/2.0f);
  renderChunks(false);
}

void chunkManager::update(int newOct, float newPer, float newFreq){ 
  //we have new persistence and octaves values, need to update our map
  if(newOct != octaves || newPer != persistence || newFreq != frequency){
    frequency = newFreq;
    octaves = newOct;
    persistence = newPer;
    updateNoise();
  }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
    chunkPosition.y -= 1;
    unloadChunk();
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
    chunkPosition.x -= 1;
    unloadChunk();
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
    chunkPosition.y += 1;
    unloadChunk();
  }
  if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
    chunkPosition.x += 1;
    unloadChunk();
  }

  sf::Vector2f playerIsoPosition = toIso(static_cast<float>(chunkPosition.x) * Chunks::size, static_cast<float>(chunkPosition.y) * Chunks::size);
  view.setCenter(
     playerIsoPosition.x + screenCenter.x, playerIsoPosition.y + screenCenter.y
  );

  window.setView(view);

  renderChunks(false);

}

/*static Chunk generateChunk(int chunkX, int chunkY, std::map<std::pair<int,int>, Chunk> *chunkToLoad,
    const siv::PerlinNoise &perlin, int octaves, float persistence, float frequency) {
    sf::Vector2i blockCoords(chunkX * Chunks::size, chunkY * Chunks::size);
    Chunk chunk;
    std::lock_guard<std::mutex> lock(mtx);
    chunk.setVisibleBlocks(blockCoords, perlin, octaves, persistence, frequency);
    return chunk;
}

/*void chunkManager::updateChunks() {
  std::vector<std::pair<int, int>> chunkCoords;
  for(int i = -Manage::renderDistance; i <= Manage::renderDistance; ++i){
    for(int j = -Manage::renderDistance; j <= Manage::renderDistance; ++j){
      int chunkX = chunkPosition.x + i;
      int chunkY = chunkPosition.y + j;
      chunkCoords.emplace_back(chunkX, chunkY);
      futures.push_back(std::async(std::launch::async, generateChunk, chunkPosition.x + i, chunkPosition.y + j,
          &chunkToLoad, perlin, octaves, persistence, frequency)); 
    }
  }
  for (size_t i = 0; i < futures.size(); ++i) {
      Chunk chunk = futures[i].get();
      std::lock_guard<std::mutex> lock(mtx);
      chunks[chunkCoords[i]] = chunk;
  }
}*/

//Updates Noise values when it finds that octaves or persistence changed
void chunkManager::updateNoise(){ 
  renderChunks(true);
}


//we see if a chunk corresponding to this coord exists (in chunk coords not game), if it does just load, otherwise create and load
void chunkManager::loadChunk(int chunkX, int chunkY, bool update){  
  sf::Vector2i blockCoords(chunkX * Chunks::size, chunkY * Chunks::size); // converted from chunk space to blocks in game space

  auto chunkIter = chunks.find({chunkX, chunkY});
  if (chunkIter == chunks.end() || update) {
    auto chunk = Chunk();
    chunk.setVisibleBlocks(blockCoords, perlin, octaves, persistence, frequency);
    chunks[{chunkX, chunkY}] = chunk;
  }
}

void chunkManager::unloadChunk(){
  for(auto it = chunks.begin(); it != chunks.end();){
    if(std::abs(chunkPosition.x - it->first.first) > Manage::renderDistance || 
       std::abs(chunkPosition.y - it->first.second) > Manage::renderDistance){
      it = chunks.erase(it);
    }else{
      it++;
    }
  }
}

void chunkManager::renderChunks(bool update){
  for(int i = -Manage::renderDistance; i <= Manage::renderDistance; ++i){
    for(int j = -Manage::renderDistance; j <= Manage::renderDistance; ++j){
      loadChunk(chunkPosition.x + i, chunkPosition.y + j, update);
    }
  }

  for(auto &pair : chunks){
    window.draw(pair.second);
  }
}
