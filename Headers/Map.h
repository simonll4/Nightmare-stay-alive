#ifndef PROYECTO_INFOII_MAP_H
#define PROYECTO_INFOII_MAP_H

#include "SFML/Graphics.hpp"

class Map {
private:

    sf::Texture *tMap;
    sf::Sprite *sMap;

public:

    Map();//constructor
    sf::Sprite &get_sprite();

    sf::Texture get_texture();
    //destructor;



};


#endif //PROYECTO_INFOII_MAP_H
