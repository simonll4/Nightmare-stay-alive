#include "../Headers/Game.h"

//Inicializadores
void Game::initializeWindow() {
    this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Nightmare!");
    int fps = 60;
    window->setFramerateLimit(fps);
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
}

void Game::update() {

    this->SFMLUpdateEvents();
    this->player1.update();
}

void Game::render() {

    this->window->clear();

    //Render items

    mapa1.get_sprite().setScale(1.2f,1.2f);
    player1.getSprite().setScale(0.9f,0.9f);

    this->window->draw(mapa1.get_sprite());

    this->window->draw(player1.getSprite());

    this->window->display();
}

void Game::run() {
    while (this->window->isOpen()) {
        this->update();
        this->render();
    }
}

