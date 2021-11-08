
#include "SFML/Graphics.hpp"

#ifndef MAIN_CPP_GUNS_H
#define MAIN_CPP_GUNS_H

using namespace std;

class Bullet{
private:

    sf::Texture *tGun;
    sf::Sprite *sGun;
    sf::Vector2f movementSpeed;
    float damage;

    float dt;
    sf::Clock dtclock;


public:
    Bullet(float dirX,float dirY, float angle);
    //~Bullet();

    void update ();
    sf::Sprite &getSprite ();

    float get_Damage();


};



#endif //MAIN_CPP_GUNS_H
