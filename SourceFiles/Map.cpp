#include "../Headers/Map.h"


Map::Map(){

 tMap = new sf::Texture;

 sMap = new sf::Sprite;

 tMap->loadFromFile("assets/mapa1.png");

 sMap->setTexture(*tMap);

}

sf::Sprite Map::get_sprite() {
    return *sMap;

}
