#include "../Entities/Enemies.h"


Enemies::Enemies() {

    tEnemy = new sf::Texture;
    sEnemy = new sf::Sprite;

    tEnemy->loadFromFile("assets/carpa.jpg");
    sEnemy->setTexture(*tEnemy);

    sEnemy->setOrigin(((float)sEnemy->getTexture()->getSize().x)/2,((float)sEnemy->getTexture()->getSize().y)/2);

    //this->currentFrame = sf::IntRect(0,0,243,224);

    //this->sEnemy->setTextureRect(sf::IntRect(this->currentFrame));

    this->hpMax = 50.f;

    this->damage = 10.f;

    this->movementSpeed = 300.f;

}

sf::Sprite &Enemies::getSprite() {
    return *sEnemy;
}



