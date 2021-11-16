#include "../Entities/Enemies.h"
#include <cmath>

////////////// INITIALIZERS //////////////

void Enemies::initVariables()
{
    srand(time(NULL));

    this->animState = ENEMY_ANIMATION_STATES::MOVE;

    this->points     = 5;
    this->hpMax = 80.f;
    this->damage = 0.7f;
    this->movementSpeed = 100.f;
}

////////////// CONSTRUCTOR ////////////////

Enemies::Enemies() {

    tEnemy = new sf::Texture;
    sEnemy = new sf::Sprite;

    tEnemy->loadFromFile("assets/Enemy/zombie_sheet(fin).png");
    sEnemy->setTexture(*tEnemy);

    //sEnemy->setOrigin(((float)sEnemy->getTexture()->getSize().x)/2,((float)sEnemy->getTexture()->getSize().y)/2);

    this->currentFrame = sf::IntRect(0,0,220,220);
    this->sEnemy->setTextureRect(sf::IntRect(this->currentFrame));


    this->initVariables();
    this->initAnimations();

}

////////////// DESTRUCTOR ////////////////

Enemies::~Enemies() {

}

////////////// GETTERS //////////////

sf::Sprite &Enemies::getSprite() {
    return *sEnemy;
}

////////////// GETTERS //////////////

float &Enemies::getSpeed() {
    return movementSpeed;
}

float Enemies::getHpmax (){
    return hpMax;
}

const int &Enemies::getPoints() const{
    return this->points;
}

////////////// SETTERS //////////////

void Enemies::setHpmax(float hp) {
    hpMax = hp;
}

void Enemies::setSpeed(float s) {
    movementSpeed = s;
}

////////////// FUNCTIONS //////////////

void Enemies::move (const float& dt, float y, float x){

    float posX;
    float posY;
    float angle;

    if(this->getSprite().getPosition().x < x){
        this->sEnemy->move(1.f * this->movementSpeed * dt, 0.f * this->movementSpeed * dt);
        if(this->animState != ENEMY_ANIMATION_STATES::ATTACK)
            this->animState = ENEMY_ANIMATION_STATES::MOVE;
    }
    if(this->getSprite().getPosition().x > x){
        this->sEnemy->move(-1.f * this->movementSpeed * dt, 0.f * this->movementSpeed * dt);
        if(this->animState != ENEMY_ANIMATION_STATES::ATTACK)
            this->animState = ENEMY_ANIMATION_STATES::MOVE;
    }
    if(this->getSprite().getPosition().y < y){
        this->sEnemy->move(0.f * this->movementSpeed * dt, 1.f * this->movementSpeed * dt);
        if(this->animState != ENEMY_ANIMATION_STATES::ATTACK)
            this->animState = ENEMY_ANIMATION_STATES::MOVE;
    }
    if(this->getSprite().getPosition().y > y){
        this->sEnemy->move(-0.f * this->movementSpeed * dt, -1.f * this->movementSpeed * dt);
        if(this->animState != ENEMY_ANIMATION_STATES::ATTACK)
            this->animState = ENEMY_ANIMATION_STATES::MOVE;
    }

    posX = x - this->sEnemy->getPosition().x;
    posY = y - this->sEnemy->getPosition().y;
    angle = -atan2(posX,posY) * 180 / 3.14159;

    this->sEnemy->setRotation(angle);

    if(this->animState != ENEMY_ANIMATION_STATES::ATTACK)
        this->animState = ENEMY_ANIMATION_STATES::MOVE;
}

////////////// ANIMATIONS //////////////

void Enemies::initAnimations()
{
    this->animationTimer.restart();
}

void Enemies::animAttack()
{
    this->animState = ENEMY_ANIMATION_STATES::ATTACK;
}

void Enemies::updateAnimations()
{
    if (this->animState == ENEMY_ANIMATION_STATES::ATTACK)
    {
        if(this->animationTimer.getElapsedTime().asSeconds() >= 0.02f)
        {
            this->currentFrame.top = 0.f;
            this->currentFrame.left += 220.f;
            if(this->currentFrame.left >= 1980.f)
                this->currentFrame.left = 0;

            this->animationTimer.restart();
            this->sEnemy->setTextureRect(this->currentFrame);
        }
        this->animState = ENEMY_ANIMATION_STATES::MOVE;
    }

    if(this->animState == ENEMY_ANIMATION_STATES::MOVE)
    {
        if(this->animationTimer.getElapsedTime().asSeconds() >= 0.030f)
        {
            this->currentFrame.top = 220.f;
            this->currentFrame.left += 220.f;
            if(this->currentFrame.left >= 3740.f)
                this->currentFrame.left = 0;

            this->animationTimer.restart();
            this->sEnemy->setTextureRect(this->currentFrame);
        }
    }
    else
        this->animationTimer.restart();
}





