#include "../Headers/Game.h"


//Inicializadores
void Game::initializeWindow() {

    this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Nightmare!");
    int fps = 60;
    window->setFramerateLimit(fps);
    view.reset(sf::FloatRect(0, 0, (float) window->getSize().x, (float) window->getSize().y));
    view.zoom(1.5f);

    tiled = new MapaTMX("assets/map2.tmx",tPlayer);

    player1 = tiled->getPlayer();

    player1->getSprite().setPosition(2216.f,1806.67);

    enemy1->getSprite().setPosition(4472.f,1909.33);

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

    this->SFMLUpdateEvents();
    this->player1->updateInputKeys(dt);
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

            std::cout << this->bullets.getSize() << "\n";
        }

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        bullets.push_back(new Bullet(player1->getSprite().getPosition().x, player1->getSprite().getPosition().y,
                                     player1->getAngle() + 90));
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
    if(player1->getSprite().getPosition().y < 520 ){
         cPos.y = 540;
     }
    if(player1->getSprite().getPosition().y > 4040){
         cPos.y = 4040;
    }

    view.setCenter(cPos);

    window->setView(view);

    this->window->draw(player1->getSprite());

    this->window->draw(enemy1->getSprite());

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

