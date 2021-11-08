#include "../Entities/Bullet.h"
#include <cmath>


Bullet::Bullet(float posX, float posY, float angle){


    tGun = new sf::Texture;
    sGun = new sf::Sprite;

    tGun->loadFromFile("assets/bullet1.png");
    sGun->setTexture(*tGun);

    movementSpeed.x = 80.0f * cos(angle*M_PI/180.0);
    movementSpeed.y = 80.0f * sin(angle*M_PI/180.0);

    sGun->setPosition(posX , posY);
    sGun->setRotation(angle);
    sGun->setScale(0.2f,0.2f);

    damage = 10.f;


}

sf::Sprite &Bullet::getSprite() {
    return *sGun;
}

void Bullet::update() {

    this->sGun->move(this->movementSpeed.x , this->movementSpeed.y);

}

float Bullet::get_Damage() {
    return this->damage;
}








