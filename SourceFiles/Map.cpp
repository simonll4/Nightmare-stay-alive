#include "../Headers/Map.h"


Map::Map(){

 tMap = new sf::Texture;

 sMap = new sf::Sprite;

 tMap->loadFromFile("assets/mapaprueba.png");

 sMap->setTexture(*tMap);

}

sf::Sprite &Map::get_sprite() {
    return *sMap;

}

sf::Texture Map::get_texture() {
    return *tMap;

}