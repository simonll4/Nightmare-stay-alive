#include "../Headers/Map.h"


Map::Map(){

 tMap = new sf::Texture;

 sMap = new sf::Sprite;

 tMap->loadFromFile("assets/map2.tmx");

 sMap->setTexture(*tMap);

 sMap->setOrigin(1800.f,1600.f);

}

sf::Sprite &Map::get_sprite() {
    return *sMap;

}

sf::Texture Map::get_texture() {
    return *tMap;

}