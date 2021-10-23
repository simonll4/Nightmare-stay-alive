#ifndef MAIN_CPP_ENEMIES_H
#define MAIN_CPP_ENEMIES_H

#include "SFML/Graphics.hpp"

class Enemies {
private:
    sf::Texture *tEnemy;
    sf::Sprite *sEnemy;
    float hp;
    float hpMax;
    float damage;
    float movementSpeed;

    //player position



public:
    Enemies();

    ~Enemies();

    //Funtions


    //Texture
    sf::Sprite &getSprite();


};


#endif //MAIN_CPP_ENEMIES_H
