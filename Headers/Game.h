#ifndef PROYECTO_INFOII_GAME_H
#define PROYECTO_INFOII_GAME_H

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "Map.h"
#include "../Entities/Bullet.h"
#include "../Entities/Player.h"
#include "../Auxiliar_Headers/LinkedList.h"
#include <vector>
#include <stack>


using namespace std;

class Game {

private:
    //Variables
    sf::RenderWindow *window;
    sf::Event sfEvent;
    Map map1;
    Player player1;
    LinkedList<Bullet*> bullets;
    sf::View view;

    //Delta time
    float dt;
    sf::Clock dtClock;
    sf::Time elapsedTime;

    //Initialize
    void initializeWindow();


public:

    Game(); //Constructor

    ~Game(); //Destructor


    //Functions
    void SFMLUpdateEvents();

    void update();

    void updateDt();

    void render();

    void run();


};


#endif //PROYECTO_INFOII_GAME_H
