#include "../Headers/Map.h"


Map::Map(){

 tMap = new sf::Texture;

 sMap = new sf::Sprite;

 tMap->loadFromFile("assets/mapa1.png");

 sMap->setTexture(*tMap);

 sMap->setOrigin(1600.f,1400.f);

}

sf::Sprite &Map::get_sprite() {
    return *sMap;

}

sf::Texture Map::get_texture() {
    return *tMap;

}