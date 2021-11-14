#include "../Entities/Player.h"
#include <cmath>
#include <iostream>

using namespace std;

void Player::initVariables()
{
    this->hpMax = 150.f;
    this->hp = this->hpMax;
    this->animState = PLAYER_ANIMATION_STATES::IDLE;
}

Player::Player(sf::Texture &tPlayer) {


    sPlayer = new sf::Sprite;

    sPlayer->setTexture(tPlayer);

    this->currentFrame = sf::IntRect(0,0,216,216);
    this->sPlayer->setTextureRect(sf::IntRect(this->currentFrame));

    //sPlayer->setOrigin(((float) sPlayer->getTexture()->getSize().x) / 2,
    //                   ((float) sPlayer->getTexture()->getSize().y) / 2);

    sPlayer->setOrigin(108,108);


    this->angle = 0.f;

    this->movementSpeed = 350.f;

    this->initVariables();
    this->initAnimations();

}

Player::~Player() = default;


sf::Sprite &Player::getSprite() {
    return *sPlayer;
}

void Player::setHp(const float hp) {
    this->hp = hp;
}

void Player::loseHp(const float value) {
    this->hp -= value;
    if (this->hp < 0) {
        this->hp = 0;
    }
}

const float &Player::getHp() const {
    return this->hp;
}

const float &Player::getHpMax() const {
    return this->hpMax;
}

void Player::setMovementSpeed(float m) {
    this->movementSpeed = m;
}

void Player::move(const float &dt, const float dir_x, const float dir_y) {
    this->sPlayer->move(dir_x * this->movementSpeed * dt, dir_y * this->movementSpeed * dt);
}


void Player::updateInputKeys(const float &dt, bool reload) {

    oldPlayerPos = sPlayer->getPosition();

    this->animState = PLAYER_ANIMATION_STATES::IDLE;

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
        this->move(dt, 0.f, -1.f);
        this->animState = PLAYER_ANIMATION_STATES::MOVING;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
        this->move(dt, -1.f, 0.f);
        this->animState = PLAYER_ANIMATION_STATES::MOVING;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
        this->move(dt, 0.f, 1.f);
        this->animState = PLAYER_ANIMATION_STATES::MOVING;
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
        this->move(dt, 1.f, 0.f);
        this->animState = PLAYER_ANIMATION_STATES::MOVING;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        this->animState = PLAYER_ANIMATION_STATES::SHOOT;
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        this->animState = PLAYER_ANIMATION_STATES::RELOAD;
    }
}

void Player::updateMouseCamera(sf::RenderWindow *win) {

    playerPos = sPlayer->getPosition();

    mouse = sf::Mouse::getPosition(*win);

    sf::Vector2f worldPos = win->mapPixelToCoords(mouse);

    a = worldPos.x - playerPos.x;
    b = worldPos.y - playerPos.y;

    angle = -atan2(a, b) * 180 / 3.14159;

    sPlayer->setRotation(angle);
}

float Player::getAngle() const {
    return angle;
}

void Player::goBack() {
    sPlayer->setPosition(oldPlayerPos);
}

void Player::initAnimations()
{
    this->animationTimer.restart();
    this->animationSwitch = true;
}

const bool &Player::getAnimSwitch()
{
    static bool anim_switch;

    anim_switch = this->animationSwitch;

    if(this->animationSwitch)
    {
        this->animationSwitch = false;
    }

    return anim_switch;
}

void Player::resetAnimationTimer()
{
    this->animationTimer.restart();
    this->animationSwitch = true;
}

void Player::updateAnimations()
{
    if (this->animState == PLAYER_ANIMATION_STATES::IDLE)
    {
        if(this->animationTimer.getElapsedTime().asSeconds() >= 0.070f || this->getAnimSwitch())
        {
            this->currentFrame.top = 0.f;
            this->currentFrame.left += 216.f;
            if(this->currentFrame.left >= 4104.f)
                this->currentFrame.left = 0;

            this->animationTimer.restart();
            this->sPlayer->setTextureRect(this->currentFrame);
        }
    }

    if(this->animState == PLAYER_ANIMATION_STATES::MOVING)
    {
        if(this->animationTimer.getElapsedTime().asSeconds() >= 0.030f || this->getAnimSwitch())
        {
            this->currentFrame.top = 216.f;
            this->currentFrame.left += 216.f;
            if(this->currentFrame.left >= 4104.f)
                this->currentFrame.left = 0;

            this->animationTimer.restart();
            this->sPlayer->setTextureRect(this->currentFrame);
        }
    }
    else if (this->animState == PLAYER_ANIMATION_STATES::RELOAD)
    {
        if(this->animationTimer.getElapsedTime().asSeconds() >= 0.008f || this->getAnimSwitch())
        {
            this->currentFrame.top = 432.f;
            this->currentFrame.left += 216.f;
            if(this->currentFrame.left >= 3240.f)
                this->currentFrame.left = 0;

            this->animationTimer.restart();
            this->sPlayer->setTextureRect(this->currentFrame);
        }
    }

    else if (this->animState == PLAYER_ANIMATION_STATES::SHOOT)
    {
        if(this->animationTimer.getElapsedTime().asSeconds() >= 0.02f || this->getAnimSwitch())
        {
            this->currentFrame.top = 648.f;
            this->currentFrame.left += 216.f;
            if(this->currentFrame.left >= 648.f)
                this->currentFrame.left = 0;

            this->animationTimer.restart();
            this->sPlayer->setTextureRect(this->currentFrame);
        }
    }
    else
        this->animationTimer.restart();
}

void Player::update()
{
    this->updateAnimations();
}



