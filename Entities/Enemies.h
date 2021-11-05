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

public:
    Enemies();

    ~Enemies();


    //Texture and Sprite
    sf::Sprite &getSprite ();
    sf::Texture &getTexture ();
    //player position
    void move (const float& dt,float x,float y);
};


#endif //MAIN_CPP_ENEMIES_H
