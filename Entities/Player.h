
#ifndef MAIN_CPP_PLAYER_H
#define MAIN_CPP_PLAYER_H

#include "SFML/Graphics.hpp"

enum PLAYER_ANIMATION_STATES {IDLE, MOVING, RELOAD, SHOOT};

class Player {
private:

    //SFML Variables
    sf::Sprite *sPlayer;
    sf::Vector2i mouse;
    sf::Vector2f playerPos;
    sf::Vector2f oldPlayerPos;

    //Variables
    double a{}, b{};
    float angle;
    float movementSpeed;

    //Animation
    sf::Clock animationTimer;
    short animState;
    sf::IntRect currentFrame;
    bool animationSwitch;

    void initAnimations();

    bool reload;

    //Core
    float hp;
    float hpMax;

    void initVariables();

public:
    //Constructors Destructors
    explicit Player(sf::Texture &tPlayer);

    ~Player();

    //Accesor
    const bool &getAnimSwitch();

    //Movement functions of player
    void move(const float &dt, float x, float y);

    void updateInputKeys(const float &dt, bool reload);

    void updateMouseCamera(sf::RenderWindow *);

    //Anim
    void resetAnimationTimer();

    void updateAnimations();

    //Getters
    sf::Sprite &getSprite();

    float getAngle() const;

    //Accesors
    const float &getHp() const;

    const float &getHpMax() const;

    void setHp(const float hp);

    void loseHp(const float value);

    //Functions
    void goBack();

    //update
    void update();
};

#endif //MAIN_CPP_PLAYER_H
