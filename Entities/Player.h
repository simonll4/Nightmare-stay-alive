
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

    //Funciones movimiento del player
    void move(const float x, const float y);
    void update();

    //Carga de texturas del player
    sf::Texture getTexture ();
    sf::Sprite &getSprite ();
    float getAngle ();
};


#endif //MAIN_CPP_PLAYER_H
