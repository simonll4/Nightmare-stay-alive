#ifndef MAIN_CPP_ENEMIES_H
#define MAIN_CPP_ENEMIES_H

#include "SFML/Graphics.hpp"
#include <time.h>

class Enemies {
private:

    sf::Texture *tEnemy;
    sf::Sprite *sEnemy;
    float hp;
    float hpMax;
    float damage;
    float movementSpeed;
    int points;
    unsigned pointCount;

    //InitVariables
    void initVariables();

public:
    Enemies();

    ~Enemies();



    //Texture and Sprite
    sf::Sprite &getSprite ();
    sf::Texture &getTexture ();

    const int& getPoints() const;
    const float& getDamage() const;

    float getHpmax();
    //player position
    void move (const float& dt,float x,float y);
    //Setters
    void setHpmax (float);
};


#endif //MAIN_CPP_ENEMIES_H

