#include "../Entities/Enemies.h"
#include <cmath>

void Enemies::initVariables()
{
    srand(time(NULL));


    this->points     = 5;
    this->hpMax = 50.f;
    this->damage = 1.f;
    this->movementSpeed = 100.f;
}

Enemies::Enemies() {

    tEnemy = new sf::Texture;
    sEnemy = new sf::Sprite;

    tEnemy->loadFromFile("assets/enemy.png");
    sEnemy->setTexture(*tEnemy);

    sEnemy->setOrigin(((float)sEnemy->getTexture()->getSize().x)/2,((float)sEnemy->getTexture()->getSize().y)/2);


    this->initVariables();

}
Enemies::~Enemies() {

}

sf::Sprite &Enemies::getSprite() {
    return *sEnemy;
}

sf::Texture &Enemies::getTexture() {
    return *tEnemy;
}

void Enemies::setHpmax(float hp) {
    hpMax = hp;
}

float Enemies::getHpmax (){
    return hpMax;
}

void Enemies::move (const float& dt, float y, float x){

    float posX;
    float posY;
    float angle;

    if(this->getSprite().getPosition().x < x){
        this->sEnemy->move(1.f * this->movementSpeed * dt, 0.f * this->movementSpeed * dt);
    }
    if(this->getSprite().getPosition().x > x){
        this->sEnemy->move(-1.f * this->movementSpeed * dt, 0.f * this->movementSpeed * dt);
    }
    if(this->getSprite().getPosition().y < y){
        this->sEnemy->move(0.f * this->movementSpeed * dt, 1.f * this->movementSpeed * dt);
    }
    if(this->getSprite().getPosition().y > y){
        this->sEnemy->move(-0.f * this->movementSpeed * dt, -1.f * this->movementSpeed * dt);
    }

    posX = x - this->sEnemy->getPosition().x;
    posY = y - this->sEnemy->getPosition().y;
    angle = -atan2(posX,posY) * 180 / 3.14159;

    this->sEnemy->setRotation(angle);

}

const int &Enemies::getPoints() const{
    return this->points;
}

const float &Enemies::getDamage() const
{
    return this->damage;
}






