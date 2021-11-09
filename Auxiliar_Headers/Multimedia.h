#ifndef MAIN_CPP_MULTIMEDIA_H
#define MAIN_CPP_MULTIMEDIA_H
#include "SFML/Audio.hpp"
#include "SFML/Graphics.hpp"
class Multimedia{
public:
    sf::Text reload;
    sf::Text game_over;
    sf::Font font;
    sf::SoundBuffer reload_buffer;
    sf::SoundBuffer reload_shout_b;
    sf::Sound reload_s;
    sf::Sound reload_shout;
    sf::SoundBuffer shot_buffer;
    sf::Sound shot;
    sf::Music background;


};
#endif //MAIN_CPP_MULTIMEDIA_H
