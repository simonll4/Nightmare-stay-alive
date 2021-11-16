#ifndef MAIN_CPP_ENEMIES_H
#define MAIN_CPP_ENEMIES_H

#include "SFML/Graphics.hpp"
#include <time.h>

enum ENEMY_ANIMATION_STATES {MOVE = 0, ATTACK};

class Enemies {
private:

    //SFML Variables
    sf::Texture *tEnemy;
    sf::Sprite *sEnemy;

    //variables
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
    //Constructir
    Enemies();

    //Destructor
    ~Enemies();



    //Texture and Sprite
    sf::Sprite &getSprite ();
    sf::Texture &getTexture ();

    //Getters
    const int& getPoints() const;
    float& getSpeed();
    float getHpmax();

    //Anim
    void updateAnimations();
    void animAttack();

    //player position
    void move (const float& dt,float x,float y);

    //Setters
    void setHpmax (float);
    void setSpeed (float);
};


#endif //MAIN_CPP_ENEMIES_H

