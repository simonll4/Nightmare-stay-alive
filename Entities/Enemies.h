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

    //Animation
    sf::IntRect currentFrame;

public:
    Enemies();

    ~Enemies();

    //Funtions
    void renderEnemies(sf::RenderTarget* target);



    //Texture
    sf::Sprite &getSprite();


};


#endif //MAIN_CPP_ENEMIES_H
