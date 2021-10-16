#include "../Entities/Player.h"
#include <cmath>
#include <iostream>
using namespace std;

Player::Player(){

    tPlayer = new sf::Texture;

    sPlayer = new sf::Sprite;

    tPlayer->loadFromFile("../assets/text_base.png");

    sPlayer->setTexture(*tPlayer);

    sPlayer->setOrigin(((float)sPlayer->getTexture()->getSize().x)/2,((float)sPlayer->getTexture()->getSize().y)/2);

    this->angle = 0.f;

    this->movementSpeed = 200.f;

}

Player::~Player() = default;


sf::Sprite &Player::getSprite() {
    return *sPlayer;
}


void Player::move(const float& dt, const float dir_x, const float dir_y){
    this->sPlayer->move(dir_x * this->movementSpeed * dt, dir_y * this->movementSpeed * dt);
}


void Player::updateInputKeys(const float &dt) {

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        this->move(dt, 0.f, -1.f);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->move(dt, -1.f, 0.f);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->move(dt, 0.f, 1.f);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->move(dt, 1.f, 0.f);
    }
}

void Player::updateMouseCamera(sf::RenderWindow *win) {

    playerPos = sPlayer->getPosition();

    mouse = sf::Mouse::getPosition(*win);

    sf::Vector2f worldPos = win->mapPixelToCoords(mouse);

    a = worldPos.x - playerPos.x;
    b = worldPos.y - playerPos.y;

    angle = -atan2(a , b) * 180 / 3.14159;

    sPlayer->setRotation(angle);
}

float Player::getAngle() const{
    return angle;
}

