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
}

void Game::render() {

    this->window->clear();

    //Render items

    this->window->draw(mapa1.get_sprite());

    this->window->display();

}

void Game::run() {
    while (this->window->isOpen()) {
        this->update();
        this->render();
    }
}

