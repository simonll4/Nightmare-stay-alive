
#include "SFML/Graphics.hpp"

#ifndef MAIN_CPP_GUNS_H
#define MAIN_CPP_GUNS_H

using namespace std;

class Bullet{
private:

    sf::Texture *tGun;
    sf::Sprite *sGun;
    int timeout;
    sf::Vector2f movementSpeed;

public:
    Bullet(float dirX,float dirY, float angle);
    //~Bullet();

    void update ();
    void move(float dirX, float dirY);

    sf::Texture getTexture();
    sf::Sprite &getSprite ();

};



#endif //MAIN_CPP_GUNS_H
