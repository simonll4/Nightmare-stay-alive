#ifndef PROYECTO_INFOII_GAME_H
#define PROYECTO_INFOII_GAME_H

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "Map.h"

using namespace std;

class Game {

private:
    //Variables
    sf::RenderWindow *window;
    sf::Event sfEvent;
    Map mapa1;

    //Inicializadores
    void initializeWindow();


public:

    Game(); //Constructor

    ~Game(); //Destructor


    //Functions
    void SFMLUpdateEvents();

    void update();

    void render();

    void run();
};


#endif //PROYECTO_INFOII_GAME_H
