#ifndef MAIN_CPP_MULTIMEDIA_H
#define MAIN_CPP_MULTIMEDIA_H
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
class Multimedia{
public:
    //Text
    sf::Text reload;
    sf::Text game_over;
    sf::Font font;

    //Sound Effects
    sf::SoundBuffer reload_buffer;
    sf::SoundBuffer reload_shout_b;
    sf::Sound reload_s;
    sf::Sound reload_shout;
    sf::SoundBuffer shot_buffer;
    sf::Sound shot;
    sf::SoundBuffer zombie_bullet_buffer;
    sf::Sound zombie_bullet;

    //Music
    sf::Music background;
    sf::Music final;


};
#endif //MAIN_CPP_MULTIMEDIA_H
