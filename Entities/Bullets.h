
#include "SFML/Graphics.hpp"

#ifndef MAIN_CPP_GUNS_H
#define MAIN_CPP_GUNS_H

using namespace std;

class Bullets{
private:

    sf::Texture *tGun;
    sf::Sprite *sGun;
    int angle;
    float movementSpeed;

public:
    Bullets();
    ~Bullets();

    //void shoot (sf::Vector2f , float angle);
    //void move(sf::Vector2f);

    sf::Texture getTexture();
    sf::Sprite &getSprite ();

};



#endif //MAIN_CPP_GUNS_H
