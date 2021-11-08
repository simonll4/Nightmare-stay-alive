#include "../Headers/Game.h"


//Inicializadores
void Game::initializeWindow() {

    this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Nightmare!");
    int fps = 60;
    window->setFramerateLimit(fps);
    view.reset(sf::FloatRect(0, 0, (float) window->getSize().x, (float) window->getSize().y));
    view.zoom(2.2f);

    clock1 = new sf::Clock();

    time1 = new float;

    tiled = new MapaTMX("assets/map2.tmx",tPlayer,enemies);

    player1 = tiled->getPlayer();

    while(!enemies.empty()){
        enemies1.push_front(enemies.front());
        enemies.pop();
    }

}

//Constructor
Game::Game() {
    tPlayer.loadFromFile("assets/text_base.png");
    this->initializeWindow();
}

//Destructor
Game::~Game() {

    delete this->window;

}

//Functions
void Game::SFMLUpdateEvents() {

    while (this->window->pollEvent(this->sfEvent)) {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();
    }
    if (sfEvent.type == sf::Event::Resized) {
        // update the view to the new size of the window
        sf::FloatRect visibleArea(0.f, 0.f, (float) sfEvent.size.width, (float) sfEvent.size.height);
        this->window->setView(sf::View(visibleArea));
    }
}

void Game::update() {

    *time1 += clock1->getElapsedTime().asSeconds();


    this->SFMLUpdateEvents();

    this->player1->updateInputKeys(dt);

    //this->tiled->collisionCheck("assets/map2.tmx",tPlayer,enemies);

    bulletZombie(enemies1, bullets);

    for (enemies1.iterInit(); !enemies1.iterEnd(); enemies1.iterNext()) {
        enemies1.iterGet()->move(dt, player1->getSprite().getPosition().y, player1->getSprite().getPosition().x);
    }

    this->player1->updateMouseCamera(this->window);


    for (bullets.iterInit(); !bullets.iterEnd(); bullets.iterNext()) {
        bullets.iterGet()->update();
    }

    for (int i = 0; i < bullets.getSize(); i++) {

        if (bullets.get(i)->getSprite().getPosition().x < view.getCenter().x - view.getSize().x / 2 ||
            bullets.get(i)->getSprite().getPosition().x > view.getCenter().x + view.getSize().x / 2 ||
            bullets.get(i)->getSprite().getPosition().y < view.getCenter().y - view.getSize().y / 2 ||
            bullets.get(i)->getSprite().getPosition().y > view.getCenter().y + view.getSize().y / 2) {

            delete this->bullets.get(i);
            this->bullets.remove(i);

        }

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if(*time1 > 450.f){
            bullets.push_back(new Bullet(player1->getSprite().getPosition().x, player1->getSprite().getPosition().y,
                                         player1->getAngle() + 90));
            *time1 = 0.f;
        }

    }
}

void Game::bulletZombie (LinkedList<Enemies*> &enemies,LinkedList<Bullet*> &bullets){
    for (int i = 0; i < bullets.getSize(); ++i) {
        for (int j = 0; j < enemies.getSize(); ++j) {
            if(bullets.get(i)->getSprite().getGlobalBounds().intersects(enemies.get(j)->getSprite().getGlobalBounds())){
                enemies.get(j)->setHpmax(enemies.get(j)->getHpmax() - bullets.get(i)->get_Damage());
                delete bullets.get(i);
                bullets.remove(i);
                if(enemies.get(j)->getHpmax() == 0){
                    delete enemies.get(j);
                    enemies.remove(j);
                }
            }
        }
    }
}

void Game::updateDt() {

    //Devuelve el tiempo que pasa y reinicia el reloj
    this->dt = this->dtClock.restart().asSeconds();
}


void Game::render() {

    this->window->clear();

    this->tiled->dibujar(*window);

    player1->getSprite().setScale(0.5f, 0.5f);
    sf::Vector2f cPos = player1->getSprite().getPosition();

    //Map setting
   if(player1->getSprite().getPosition().x > 3550){
        cPos.x = 3550;
    }
    if(player1->getSprite().getPosition().x < 1050){
        cPos.x = 1050;
    }
    if(player1->getSprite().getPosition().y < 540 ){
         cPos.y = 540;
     }
    if(player1->getSprite().getPosition().y > 4040){
         cPos.y = 4040;
    }

    view.setCenter(cPos);

    window->setView(view);

    this->window->draw(player1->getSprite());

    for (enemies1.iterInit();!enemies1.iterEnd();enemies1.iterNext()) {
            this->window->draw(enemies1.iterGet()->getSprite());
        }


    for (int i = 0; i < bullets.getSize(); ++i) {
        window->draw(bullets.get(i)->getSprite());
    }

    this->window->display();
}

void Game::run() {
    while (this->window->isOpen()) {

        //Update clock
        this->updateDt();

        //Update frame
        this->update();

        //Render frame
        this->render();
    }
}

