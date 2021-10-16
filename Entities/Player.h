
#ifndef MAIN_CPP_PLAYER_H
#define MAIN_CPP_PLAYER_H

#include "SFML/Graphics.hpp"

class Player {
private:
    sf::Texture *tPlayer;
    sf::Sprite *sPlayer;
    sf::Vector2i mouse;
    sf::Vector2f playerPos;
    double a{}, b{};
    float angle;
    float movementSpeed;

public:
    //Constructors Destructors
    Player();
    ~Player();

    //Funciones movimiento del player
    void move(const float x, const float y);
    void updateKeys();
    void updateMouseCamera(sf::RenderWindow*);


    //Carga de texturas del player

    sf::Sprite &getSprite ();
    float getAngle () const;

};


#endif //MAIN_CPP_PLAYER_H
