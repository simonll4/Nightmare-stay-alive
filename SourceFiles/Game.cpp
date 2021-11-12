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

    tiled = new MapaTMX("assets/map2.tmx", tPlayer, enemies);

    player1 = tiled->getPlayer();

    while (!enemies.empty()) {
        enemies1.push_front(enemies.front());
        enemies.pop();
    }
    if (!multimedia.background.openFromFile("assets/backgroundMusic.ogg")) {
        cout << "No se pudo cargar la musica" << endl;
    }
    multimedia.background.setVolume(1.f);
    multimedia.background.setLoop(true);
    multimedia.background.play();

    if (this->player1->getHp() <= 0) {
        if (!this->multimedia.final.openFromFile("assets/death_final_1.ogg")) {
            cout << "No se pudo cargar el audio" << endl;
        }
        this->multimedia.background.stop();
        this->multimedia.final.setVolume(75);
        this->multimedia.final.setLoop(true);
        this->multimedia.final.play();
    }
}

//Constructor
Game::Game() {
    tPlayer.loadFromFile("assets/text_base.png");
    this->initializeWindow();
    this->initGUI();
    this->initSystems();
}

//Destructor
Game::~Game() {

    delete this->window;

}

void Game::initSystems() {
    this->points = 0;
}

void Game::initGUI() {
    //Load font
    if (!this->font.loadFromFile("assets/btseps2.TTF")) {
        std::cout << "ERROR::GAME::Failed to load font" << "\n";
    }

    //init point text
    this->pointText.setFont(this->font);
    this->pointText.setCharacterSize(50);
    this->pointText.setFillColor(sf::Color::Red);
    this->pointText.setString("test");

    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(300);
    this->gameOverText.setFillColor(sf::Color::Red);
    this->gameOverText.setString("GAME OVER");
    this->gameOverText.setOrigin(this->gameOverText.getGlobalBounds().width / 2,
                                 this->gameOverText.getGlobalBounds().height / 2);


    this->playerHpBar.setSize(sf::Vector2f(250.f, 15.f));
    this->playerHpBar.setFillColor(sf::Color::Green);

    this->playerHpBack = this->playerHpBar;
    this->playerHpBack.setFillColor(sf::Color(25, 25, 25, 200));
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

    *time1 = clock1->getElapsedTime().asSeconds();

    this->player1->updateInputKeys(dt);
    if (tiled->collitionCheck(player1->getSprite().getGlobalBounds())) {
        player1->goBack();
    }

    this->updateGUI();

    //this->tiled->collisionCheck("assets/map2.tmx",tPlayer,enemies);

    playerZombie(enemies1, *player1);

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

    if (this->charger > 25) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            if (!multimedia.reload_buffer.loadFromFile("assets/reloadgun.wav")) {
                cout << "no se pudo cargar el sonido" << endl;
            }
            multimedia.reload_s.setBuffer(multimedia.reload_buffer);
            multimedia.reload_s.setVolume(80.f);
            multimedia.reload_s.play();
            if (!multimedia.reload_shout_b.loadFromFile("assets/shout_reload.wav")) {
                cout << "no se pudo cargar el segundo sonido" << endl;
            }
            multimedia.reload_shout.setBuffer(multimedia.reload_shout_b);
            multimedia.reload_shout.play();
            this->charger = 0;
        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (*time1 > 0.3f) {

            if (this->charger <= 25) {
                bullets.push_back(new Bullet(player1->getSprite().getPosition().x, player1->getSprite().getPosition().y,
                                             player1->getAngle() + 90));
                if (!multimedia.shot_buffer.loadFromFile("assets/shot.wav")) {
                    cout << "No se pudo abrir el sonido" << endl;
                }
                multimedia.shot.setBuffer(multimedia.shot_buffer);
                multimedia.shot.setVolume(15.f);
                multimedia.shot.play();
                clock1->restart();
                this->charger++;
            }
        }
    }


}

void Game::bulletZombie(LinkedList<Enemies *> &enemies, LinkedList<Bullet *> &bullets) {
    for (int j = 0; j < enemies.getSize(); ++j) {
        for (int i = 0; i < bullets.getSize(); ++i) {
            if (bullets.get(i)->getSprite().getGlobalBounds().intersects(
                    enemies.get(j)->getSprite().getGlobalBounds())) {
                if (!this->multimedia.zombie_bullet_buffer.loadFromFile("assets/zombiegrr.wav")) {
                    cout << "No se pudo cargar el audio" << endl;
                }
                this->multimedia.zombie_bullet.setBuffer(this->multimedia.zombie_bullet_buffer);
                this->multimedia.zombie_bullet.setVolume(50);
                this->multimedia.zombie_bullet.play();
                enemies.get(j)->setHpmax(enemies.get(j)->getHpmax() - bullets.get(i)->get_Damage());
                delete bullets.get(i);
                bullets.remove(i);
                if (enemies.get(j)->getHpmax() == 0) {
                    this->points += enemies.get(j)->getPoints();
                    cout << points << endl;
                    delete enemies.get(j);
                    enemies.remove(j);
                }
            }
        }
    }
}

void Game::playerZombie(LinkedList<Enemies *> &enemies1, Player player1) {
    for (int i = 0; i < enemies1.getSize(); ++i) {
        if (player1.getSprite().getGlobalBounds().intersects(enemies1.get(i)->getSprite().getGlobalBounds())) {
            this->player1->loseHp(0.2f);
        }
    }
}

void Game::updateGUI() {
    std::stringstream ss;
    ss << "Points: " << this->points;
    this->pointText.setString(ss.str());
    this->pointText.setPosition(player1->getSprite().getPosition().x - window->getSize().x / 2,
                                player1->getSprite().getPosition().y - window->getSize().y / 2);


    this->gameOverText.setPosition(this->player1->getSprite().getPosition().x - 325,
                                   this->player1->getSprite().getPosition().y - 200);

    this->playerHpBar.setPosition(sf::Vector2f(this->player1->getSprite().getPosition().x - 70.f,
                                               this->player1->getSprite().getPosition().y - 100.f));

    //Update playerGUI
    this->player1->setHp(this->player1->getHp());
    float hpPercent = static_cast<float>(this->player1->getHp()) / this->player1->getHpMax() * 100;
    this->playerHpBar.setSize(sf::Vector2f(1.5f * hpPercent, this->playerHpBar.getSize().y));
}

void Game::updateDt() {

    //Devuelve el tiempo que pasa y reinicia el reloj
    this->dt = this->dtClock.restart().asSeconds();
}

void Game::renderGUI() {
    this->window->draw(this->pointText);
    this->window->draw(this->playerHpBack);
    this->window->draw(this->playerHpBar);
}


void Game::render() {

    this->window->clear();

    if (this->player1->getHp() > 0) {
        this->tiled->dibujar(*window);
        player1->getSprite().setScale(0.5f, 0.5f);
        sf::Vector2f cPos = player1->getSprite().getPosition();

        //Map setting
        if (player1->getSprite().getPosition().x > 3200) {
            cPos.x = 3200;
        }
        if (player1->getSprite().getPosition().x < 1400) {
            cPos.x = 1400;
        }
        if (player1->getSprite().getPosition().y < 800) {
            cPos.y = 800;
        }
        if (player1->getSprite().getPosition().y > 3760) {
            cPos.y = 3760;
        }

        view.setCenter(cPos);

        window->setView(view);

        this->window->draw(player1->getSprite());
        sf::FloatRect aux = player1->getSprite().getGlobalBounds();
        sf::RectangleShape p({aux.width, aux.height});
        p.setPosition({aux.left, aux.top});
        p.setOutlineColor(sf::Color::Green);
        p.setFillColor(sf::Color::Transparent);
        p.setOutlineThickness(3);
        this->window->draw(p);

        for (enemies1.iterInit(); !enemies1.iterEnd(); enemies1.iterNext()) {
            this->window->draw(enemies1.iterGet()->getSprite());
        }

        for (int i = 0; i < bullets.getSize(); ++i) {
            window->draw(bullets.get(i)->getSprite());
        }
        if (!multimedia.font.loadFromFile("assets/gameFont.ttf"))
            cout << "NO SE PUDO CARGAR LA FUENTE" << endl;

        multimedia.reload.setFont(multimedia.font);
        multimedia.reload.setString("Press R to RELOAD");
        multimedia.reload.setCharacterSize(56);
        multimedia.reload.setFillColor(sf::Color::Red);
        multimedia.reload.setPosition(player1->getSprite().getPosition().x + 50,
                                      player1->getSprite().getPosition().y + 50);
        if (this->charger > 25) {
            this->window->draw(multimedia.reload);
        }

        this->renderGUI();

    } else {
        this->window->draw(this->gameOverText);
        ofstream leaderboard;
        leaderboard.open("Leaderboard.txt", ios::app);
        leaderboard << "Ultima Partida" << "\n" << "Puntos: " << points << "\n" << "Tiempo: "
                    << gameTime.getElapsedTime().asSeconds() << " Segundos " << endl;
        leaderboard << endl;
        leaderboard.close();

    }
    this->window->display();
}

void Game::run() {
    while (this->window->isOpen()) {
        if (this->player1->getHp() > 0) {
            //Update clock
            this->updateDt();

            //Update window events
            this->SFMLUpdateEvents();

            //Update frame
            this->update();

            //Render frame
            this->render();

        } else if (this->player1->getHp() <= 0) {
            this->multimedia.background.stop();

            if(elapsedTime == 0){
                if (!this->multimedia.final.openFromFile("assets/death_final_1.ogg")) {
                    cout << "No se pudo cargar el audio" << endl;
                }
                this->multimedia.final.setVolume(75);
                this->multimedia.final.play();
                elapsedTime = 1;
            }

            elapsedTime++;
            cout << this->elapsedTime << endl;
            if (this->elapsedTime > 10000) {
                this->window->close();
            }
        }
    }
}

