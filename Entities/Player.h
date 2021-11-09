
#ifndef MAIN_CPP_PLAYER_H
#define MAIN_CPP_PLAYER_H

#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"


class Player {
private:
    sf::Sprite *sPlayer;
    sf::Vector2i mouse;
    sf::Vector2f playerPos;
    double a{}, b{};
    float angle;
    float movementSpeed;
    int hp;

public:
    //Constructors Destructors
    explicit Player(sf::Texture &tPlayer);
    ~Player();

    //Movement functions of player
    void move(const float& dt, float x, float y);
    void updateInputKeys(const float& dt);
    void updateMouseCamera(sf::RenderWindow*);


    //Carga de texturas del player
    sf::Sprite &getSprite ();
    float getAngle () const;

    //Setters
    void setMovementSpeed (float);
    void setHp (int);

    //Getters
    int getHp ();

    //Multimedia
    sf::SoundBuffer steps_buffer;
    sf::Sound steps;
};


#endif //MAIN_CPP_PLAYER_H
