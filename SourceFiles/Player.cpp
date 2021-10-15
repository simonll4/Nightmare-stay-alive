#include "../Entities/Player.h"
#include <cmath>

Player::Player(){

    tPlayer = new sf::Texture;

    sPlayer = new sf::Sprite;

    tPlayer->loadFromFile("../assets/text_base.png");

    sPlayer->setTexture(*tPlayer);

    sPlayer->setOrigin((float)sPlayer->getTexture()->getSize().x/2,(float)sPlayer->getTexture()->getSize().y/2);

    this->angle = 0.f;

    this->movementSpeed = 5.f;

}

Player::~Player(){

}


sf::Sprite &Player::getSprite() {
    return *sPlayer;
}


void Player::move(const float dir_x, const float dir_y){
    this->sPlayer->move(dir_x * this->movementSpeed, dir_y * this->movementSpeed);
}


void Player::update(sf::Window *w){

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        this->move(0.f, -1.f);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->move(-1.f, 0.f);
    }


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->move(0.f, 1.f);
    }


    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->move(1.f, 0.f);
    }

    angle = ((atanf((sf::Mouse::getPosition(*w).y-sPlayer->getPosition().y)/(sf::Mouse::getPosition(*w).x-sPlayer->getPosition().x)))*360)/M_2_PI;
    sPlayer->setRotation(angle);

}

float Player::getAngle(){
    return angle;
};


