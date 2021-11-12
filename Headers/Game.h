#ifndef PROYECTO_INFOII_GAME_H
#define PROYECTO_INFOII_GAME_H

#include <iostream>
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include "SFML/Window.hpp"
#include "SFML/Audio.hpp"
#include "TiledMap.h"
#include "../Entities/Bullet.h"
#include "../Entities/Player.h"
#include "../Entities/Enemies.h"
#include "../Auxiliar_Headers/LinkedList.h"
#include "../Auxiliar_Headers/Multimedia.h"
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <sstream>
#include <fstream>


using namespace std;

class Game {

private:
    //Variables
    sf::RenderWindow *window;
    sf::RenderWindow *leaderboard;
    sf::Event sfEvent;
    Player* player1;
    queue<Enemies*> enemies;
    LinkedList<Enemies*> enemies1;
    LinkedList<Bullet*> bullets;
    sf::View view;
    sf::Texture tPlayer;
    MapaTMX* tiled;
    Multimedia multimedia;
    stack<int> charger;





    //GUI
    sf::Font font;
    sf::Text pointText;

   //text
    sf::Text gameOverText;

    //Systems
    unsigned points;

    //Delta time
    float dt;
    sf::Clock dtClock;
    float elapsedTime = 0;
    sf::Clock * clock1;
    float * time1;
    sf::Clock gameTime;

    //Initialize
    void initializeWindow();

    //PlayerGUI
    sf::RectangleShape playerHpBar;
    sf::RectangleShape playerHpBack;

    void initGUI();
    void initSystems();


public:

    Game(); //Constructor

    ~Game(); //Destructor


    //Functions
    void SFMLUpdateEvents();

    void update();

    void updateDt();

    void updateGUI();

    void render();

    void renderGUI();

    void run();

    void bulletZombie(LinkedList<Enemies*> &enemies1,LinkedList<Bullet*> &bullets);
    void playerZombie(LinkedList<Enemies*> &enemies1,Player player1);




};


#endif //PROYECTO_INFOII_GAME_H
