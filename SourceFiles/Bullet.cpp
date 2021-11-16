#include "../Entities/Bullet.h"
#include <cmath>

////////////// CONSTRUCTOR ////////////////

Bullet::Bullet(float posX, float posY, float angle){


    tGun = new sf::Texture;
    sGun = new sf::Sprite;

    tGun->loadFromFile("assets/Images/bullet1.png");
    sGun->setTexture(*tGun);

    movementSpeed.x = 80.0f * cos(angle*M_PI/180.0);
    movementSpeed.y = 80.0f * sin(angle*M_PI/180.0);

    sGun->setPosition(posX , posY);
    sGun->setRotation(angle);
    sGun->setScale(0.2f,0.2f);

    damage = 10.f;


}

////////////// GETTERS //////////////

sf::Sprite &Bullet::getSprite() {
    return *sGun;
}

float Bullet::get_Damage() {
    return this->damage;
}

////////////// UPDATERS //////////////

void Bullet::update() {

    this->sGun->move(this->movementSpeed.x , this->movementSpeed.y);

}








