#include "../Headers/Game.h"


//Inicializadores
void Game::initializeWindow() {

    this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Nightmare!");
    int fps = 60;
    window->setFramerateLimit(fps);
    view.reset(sf::FloatRect(0,0,1920,1080));
}

//Constructor
Game::Game() {

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
    if (sfEvent.type == sf::Event::Resized)
    {
        // update the view to the new size of the window
        sf::FloatRect visibleArea(0.f, 0.f, sfEvent.size.width, sfEvent.size.height);
        this->window->setView(sf::View(visibleArea));
    }
}

void Game::update() {

    this->SFMLUpdateEvents();
    this->player1.updateInputKeys(dt);
    this->player1.updateMouseCamera(this->window);

    for (int i = 0; i < bullets.getSize(); ++i) {
        bullets.get(i)->update();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)){
        bullets.push_front(new Bullet (player1.getSprite().getPosition().x, player1.getSprite().getPosition().y,player1.getAngle()+90));
    }

}

void Game::updateDt() {

    //Devuelve el tiempo que pasa y reinicia el reloj
    this->dt = this->dtClock.restart().asSeconds();
}


void Game::render() {

    this->window->clear();

    //Render items
    mapa1.get_sprite().setScale(0.9f,0.9f);
    player1.getSprite().setScale(0.5f,0.5f);

    window->setView(view);
    view.setCenter(player1.getSprite().getPosition());

    this->window->draw(mapa1.get_sprite());

    this->window->draw(player1.getSprite());

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

