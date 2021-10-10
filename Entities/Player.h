
#ifndef MAIN_CPP_PLAYER_H
#define MAIN_CPP_PLAYER_H

#include "SFML/Graphics.hpp"

class Player {
private:
    sf::Texture *tPlayer;
    sf::Sprite *sPlayer;
    float angle;
    float movementSpeed;

public:
    //Constructors Destructors
    Player();
    ~Player();

    void move(const float x, const float y);
    void update();


    sf::Texture getTexture ();
    sf::Sprite &getSprite ();
};


#endif //MAIN_CPP_PLAYER_H
