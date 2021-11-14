#ifndef MAIN_CPP_ENEMIES_H
#define MAIN_CPP_ENEMIES_H

#include "SFML/Graphics.hpp"
#include <time.h>

enum ENEMY_ANIMATION_STATES {MOVE = 0, ATTACK};

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

    //Animation
    sf::Clock animationTimer;
    short animState;
    sf::IntRect currentFrame;
    bool animationSwitch;
    void initAnimations();

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
    float& getSpeed();

    //Anim
    void updateAnimations();
    void animAttack();

    float getHpmax();
    //player position
    void move (const float& dt,float x,float y);
    //Setters
    void setHpmax (float);
    void setSpeed (float);
};


#endif //MAIN_CPP_ENEMIES_H

