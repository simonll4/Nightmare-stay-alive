#include "../Headers/Game.h"


//Inicializadores
void Game::initializeWindow() {

    this->window = new sf::RenderWindow(sf::VideoMode(1920, 1080), "Nightmare!");
    int fps = 60;
    window->setFramerateLimit(fps);
    view.reset(sf::FloatRect(0,0,(float)window->getSize().x,(float)window->getSize().y));
    view.zoom(1.5f);

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
        sf::FloatRect visibleArea(0.f, 0.f, (float)sfEvent.size.width, (float)sfEvent.size.height);
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

    for (int i = 0; i < bullets.getSize(); i++) {

        if(bullets.get(i)->getSprite().getPosition().x < 0 || bullets.get(i)->getSprite().getPosition().x > window->getSize().x || bullets.get(i)->getSprite().getPosition().y < 0 || bullets.get(i)->getSprite().getPosition().y > window->getSize().y){

            delete this->bullets.get(i);
            this-> bullets.remove(i);

            std::cout << this->bullets.getSize() << "\n";
        }

    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        bullets.push_back(new Bullet(player1.getSprite().getPosition().x, player1.getSprite().getPosition().y,player1.getAngle() + 90));
    }
}


void Game::updateDt() {

    //Devuelve el tiempo que pasa y reinicia el reloj
    this->dt = this->dtClock.restart().asSeconds();
}


void Game::render() {

    this->window->clear();

    //Render items
    map1.get_sprite().setScale(0.9f, 0.9f);
    player1.getSprite().setScale(0.5f,0.5f);


    view.setCenter(player1.getSprite().getPosition());
    window->setView(view);

    this->window->draw(map1.get_sprite());

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

