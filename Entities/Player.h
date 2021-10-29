
#ifndef MAIN_CPP_PLAYER_H
#define MAIN_CPP_PLAYER_H

#include "SFML/Graphics.hpp"

class Player {
private:
    sf::Sprite *sPlayer;
    sf::Vector2i mouse;
    sf::Vector2f playerPos;
    double a{}, b{};
    float angle;
    float movementSpeed;

public:
    //Constructors Destructors
    explicit Player(sf::Texture &tPlayer);
    ~Player();

    //Movement functions of player
    void move(const float& dt, float x, float y);
    void updateInputKeys(const float& dt);
    void updateMouseCamera(sf::RenderWindow*);


    //Carga de texturas del player
    sf::Sprite &getSprite ();
    float getAngle () const;


};


#endif //MAIN_CPP_PLAYER_H
