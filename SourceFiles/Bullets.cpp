#include "../Entities/Bullets.h"


Bullets::Bullets(){


    tGun = new sf::Texture;
    sGun = new sf::Sprite;

    tGun->loadFromFile("assets/bullet1.png");
    sGun->setTexture(*tGun);

    movementSpeed = 7.f;

}

sf::Sprite &Bullets::getSprite() {
    return *sGun;
}


