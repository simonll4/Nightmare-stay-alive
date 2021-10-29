#ifndef PROYECTO_INFOII_GAME_H
#define PROYECTO_INFOII_GAME_H

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "Map.h"
#include "TiledMap.h"
#include "../Entities/Bullet.h"
#include "../Entities/Player.h"
#include "../Entities/Enemies.h"
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
    Player* player1;
    LinkedList<Bullet*> bullets;
    sf::View view;
    sf::Texture tPlayer;

    MapaTMX* tiled;




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

    //enemies




};


#endif //PROYECTO_INFOII_GAME_H
