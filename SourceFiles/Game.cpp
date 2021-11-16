#include "../Headers/Game.h"

///////////////////////////////////////////////////////////
/////////////////// CONSTRUCTOR ///////////////////////////
///////////////////////////////////////////////////////////

Game::Game() {
    tPlayer.loadFromFile("assets/Player/player_s_fin.png");

    this->initializeWindow();
    this->initGUI();
    this->initSystems();
}

///////////////////////////////////////////////////////////
/////////////////// DESTRUCTOR ////////////////////////////
///////////////////////////////////////////////////////////

Game::~Game() {

    delete this->window;
    delete this->leaderboard;

}

///////////////////////////////////////////////////////////
/////////////////// INITIALIZERS //////////////////////////
///////////////////////////////////////////////////////////

void Game::initializeWindow() {

    this->leaderboard = new sf::RenderWindow(sf::VideoMode(1280, 720), "Leaderboard");
    this->window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Nightmare!");

    int fps = 60;
    window->setFramerateLimit(fps);
    leaderboard->setFramerateLimit(fps);
    view.reset(sf::FloatRect(0, 0, (float) window->getSize().x, (float) window->getSize().y));
    view.zoom(2.2f);

    clock1 = new sf::Clock();

    time1 = new float;

    tiled = new MapaTMX("assets/map2.tmx", tPlayer, enemies);

    player1 = tiled->getPlayer();

    for (int i = 0; i < 17; ++i) {
        charger.push(1);
    }

    while (!enemies.empty()) {
        enemies1.push_front(enemies.front());
        enemies.pop();
    }
    if (!multimedia.background.openFromFile("assets/Audio/backgroundMusic.ogg")) {
        cout << "No se pudo cargar la musica" << endl;
    }
    multimedia.background.setVolume(5);
    multimedia.background.setLoop(true);
    multimedia.background.play();

    if (this->player1->getHp() <= 0) {
        if (!this->multimedia.final.openFromFile("assets/Audio/death_final_1.ogg")) {
            cout << "No se pudo cargar el audio" << endl;
        }
        this->multimedia.background.stop();
        this->multimedia.final.setVolume(100);
        this->multimedia.final.setLoop(true);
        this->multimedia.final.play();
    }

    this->player1->getSprite().setScale(2.0f, 2.0f);
}

void Game::initSystems() {
    this->points = 0;
}

void Game::initGUI() {
    //Load font
    if (!this->font.loadFromFile("assets/Text/btseps2.TTF")) {
        std::cout << "ERROR::GAME::Failed to load font" << "\n";
    }

    //init point text
    this->pointText.setFont(this->font);
    this->pointText.setCharacterSize(50);
    this->pointText.setFillColor(sf::Color::Red);
    this->pointText.setString("test");


    this->playerHpBar.setSize(sf::Vector2f(250.f, 15.f));
    this->playerHpBar.setFillColor(sf::Color::Green);

    this->playerHpBack = this->playerHpBar;
    this->playerHpBack.setFillColor(sf::Color(25, 25, 25, 200));
}

///////////////////////////////////////////////////////////
//////////////////// UPDATERS /////////////////////////////
///////////////////////////////////////////////////////////

void Game::SFMLUpdateEvents() {

    while (this->window->pollEvent(this->sfEvent)) {
        if (this->sfEvent.type == sf::Event::Closed)
            this->window->close();

        if(this->sfEvent.type == sf::Event::KeyReleased &&
        (this->sfEvent.key.code == sf::Keyboard::A||
        this->sfEvent.key.code == sf::Keyboard::D ||
        this->sfEvent.key.code == sf::Keyboard::W ||
        this->sfEvent.key.code == sf::Keyboard::S ||
        this->sfEvent.key.code == sf::Keyboard::Space ||
        this->sfEvent.key.code == sf::Keyboard::R))
        {
            this->player1->resetAnimationTimer();
        }
    }


    if (sfEvent.type == sf::Event::Resized) {
        // update the view to the new size of the window
        sf::FloatRect visibleArea(0.f, 0.f, (float) sfEvent.size.width, (float) sfEvent.size.height);
        this->window->setView(sf::View(visibleArea));
    }

    while (this->leaderboard->pollEvent(this->sfEvent)) {
        if (this->sfEvent.type == sf::Event::Closed) {
            this->leaderboard->close();
        }
    }
}

void Game::update() {

    *time1 = clock1->getElapsedTime().asSeconds();

    this->player1->updateInputKeys(dt, false);
    if (tiled->collisionCheck(player1->getSprite().getGlobalBounds())) {
        player1->goBack();
    }

    this->player1->update();

    this->updateGUI();

    playerZombie(enemies1, *player1);

    bulletZombie(enemies1, bullets);



    for (enemies1.iterInit(); !enemies1.iterEnd(); enemies1.iterNext()) {
        enemies1.iterGet()->move(dt, player1->getSprite().getPosition().y, player1->getSprite().getPosition().x);
        this->enemies1.iterGet()->updateAnimations();
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

    if (charger.empty()) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
            if (!multimedia.reload_buffer.loadFromFile("assets/Audio/reloadgun.wav")) {
                cout << "no se pudo cargar el sonido" << endl;
            }
            multimedia.reload_s.setBuffer(multimedia.reload_buffer);
            multimedia.reload_s.setVolume(80.f);
            multimedia.reload_s.play();
            if (!multimedia.reload_shout_b.loadFromFile("assets/Audio/shout_reload.wav")) {
                cout << "no se pudo cargar el segundo sonido" << endl;
            }
            multimedia.reload_shout.setBuffer(multimedia.reload_shout_b);
            multimedia.reload_shout.play();

            this->player1->updateInputKeys(dt, true);

            for (int i = 0; i < 17; ++i) {
                charger.push(1);
            }

        }
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        if (*time1 > 0.3f) {

            if (!this->charger.empty()) {
                bullets.push_back(new Bullet(player1->getSprite().getPosition().x, player1->getSprite().getPosition().y,
                                             player1->getAngle() + 90));
                if (!multimedia.shot_buffer.loadFromFile("assets/Audio/shot.wav")) {
                    cout << "No se pudo abrir el sonido" << endl;
                }
                multimedia.shot.setBuffer(multimedia.shot_buffer);
                multimedia.shot.setVolume(15.f);
                multimedia.shot.play();
                clock1->restart();
                this->charger.pop();


            }
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

///////////////////////////////////////////////////////////
////////////////// COLLISIONS /////////////////////////////
///////////////////////////////////////////////////////////

void Game::bulletZombie(LinkedList<Enemies *> &enemies, LinkedList<Bullet *> &bullets) {
    for (int j = 0; j < enemies.getSize(); ++j) {
        for (int i = 0; i < bullets.getSize(); ++i) {
            if (bullets.get(i)->getSprite().getGlobalBounds().intersects(
                    enemies.get(j)->getSprite().getGlobalBounds())) {


                if (!this->multimedia.zombie_bullet_buffer.loadFromFile("assets/Audio/zombiegrr.wav")) {
                    cout << "No se pudo cargar el audio" << endl;
                }
                this->multimedia.zombie_bullet.setBuffer(this->multimedia.zombie_bullet_buffer);
                this->multimedia.zombie_bullet.setVolume(50);
                this->multimedia.zombie_bullet.play();
                enemies.get(j)->setHpmax(enemies.get(j)->getHpmax() - bullets.get(i)->get_Damage());
                enemies.get(j)->setSpeed(enemies.get(j)->getSpeed() + 40.f);
                delete bullets.get(i);
                bullets.remove(i);
                if (enemies.get(j)->getHpmax() == 0) {
                    this->points += enemies.get(j)->getPoints();
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
            this->enemies1.get(i)->animAttack();
            this->player1->loseHp(0.2f);
        }
    }

}

///////////////////////////////////////////////////////////
/////////////////// RENDERERS /////////////////////////////
///////////////////////////////////////////////////////////

void Game::renderGUI() {
    this->window->draw(this->pointText);
    this->window->draw(this->playerHpBack);
    this->window->draw(this->playerHpBar);
}


void Game::render() {

    this->window->clear();

    if (this->player1->getHp() > 0) {

        this->tiled->dibujar(*window);
        player1->getSprite().setScale(0.8f, 0.8f);
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

        for (enemies1.iterInit(); !enemies1.iterEnd(); enemies1.iterNext()) {
            this->window->draw(enemies1.iterGet()->getSprite());
        }

        for (int i = 0; i < bullets.getSize(); ++i) {
            window->draw(bullets.get(i)->getSprite());
        }
        if (!multimedia.font.loadFromFile("assets/Text/gameFont.ttf"))
            cout << "NO SE PUDO CARGAR LA FUENTE" << endl;

        multimedia.reload.setFont(multimedia.font);
        multimedia.reload.setString("Press R to RELOAD");
        multimedia.reload.setCharacterSize(56);
        multimedia.reload.setFillColor(sf::Color::Red);
        multimedia.reload.setPosition(player1->getSprite().getPosition().x + 50,
                                      player1->getSprite().getPosition().y + 50);
        if (this->charger.empty()) {
            this->window->draw(multimedia.reload);
        }

        this->renderGUI();
    }
    this->window->display();
}

void Game::renderLeaderboard() {
    leaderboard->clear();

    sf::Event rollEvent;

    this->leaderboardBack.loadFromFile("assets/Images/mainmenu.png");
    this->sleaderboardBack.setTexture(leaderboardBack);
    this->sleaderboardBack.setScale(1.28, 1.13);
    this->leaderboard->draw(sleaderboardBack);

    this->gameOverText.setFont(this->font);
    this->gameOverText.setCharacterSize(150);
    this->gameOverText.setFillColor(sf::Color::White);
    this->gameOverText.setString("GAME OVER");
    this->gameOverText.setOrigin(this->gameOverText.getGlobalBounds().width / 2,
                                 this->gameOverText.getGlobalBounds().height / 2);
    this->gameOverText.setPosition(leaderboard->getSize().x / 2, leaderboard->getSize().y / 10);


    this->leaderboard->draw(this->gameOverText);

    ifstream game;
    std::string oldData;
    game.open("Leaderboard.txt");
    if (game.is_open()) {
        while (!game.eof()) {
            oldData += game.get();
        }
        game >> oldData;
        game.close();
    }
    this->Olddata.setString(oldData);
    Olddata.setFont(font);
    Olddata.setCharacterSize(50);
    Olddata.setFillColor(sf::Color::White);
    Olddata.setPosition(leaderboard->getSize().x / 6, leaderboard->getSize().y / 4);

    this->leaderboard->draw(Olddata);

    leaderboard->display();
}


///////////////////////////////////////////////////////////
///////////////////////// RUN /////////////////////////////
///////////////////////////////////////////////////////////

void Game::run() {
    while (this->window->isOpen()) {
        if (this->player1->getHp() > 0 && enemies1.getSize() != 0) {
            //Update clock
            this->updateDt();

            //Update window events
            this->SFMLUpdateEvents();

            //Update frame
            this->update();

            //Render frame
            this->render();
        } else {
            this->window->close();
        }
    }
    while (this->leaderboard->isOpen()) {

        if (this->player1->getHp() <= 0 || enemies1.getSize() == 0) {

            this->SFMLUpdateEvents();

            this->renderLeaderboard();

            this->multimedia.background.stop();
            if (elapsedTime == 0) {
                gametime = gameTime.getElapsedTime().asSeconds();
                if (!this->multimedia.final.openFromFile("assets/Audio/death_final_1.ogg")) {
                    cout << "No se pudo cargar el audio" << endl;
                }
                this->multimedia.final.setVolume(1.f);
                this->multimedia.final.play();
                elapsedTime = 1;
                ofstream game;
                game.open("Leaderboard.txt", ios::app);
                game << "Datos de Partida" << "\n" << "Puntos: " << points << "\n" << "Tiempo: "
                     << gametime << " Segundos " << endl;
                game << endl;
                game.close();

            }
        }
    }
}




