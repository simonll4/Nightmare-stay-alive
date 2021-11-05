
#ifndef TESTSFML_MAPATMX_H
#define TESTSFML_MAPATMX_H

#include <tmxlite/Map.hpp>
#include <tmxlite/Layer.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/TileLayer.hpp>
#include <SFML/Graphics.hpp>
#include <string>
#include "../Auxiliar_Headers/LinkedList.h"
#include "../Entities/Player.h"
#include "../Entities/Enemies.h"
#include <queue>

using namespace std;

class MapaTMX {
private:
    tmx::Map map;
    sf::Texture textura;
    LinkedList<sf::Sprite *> sprites;
    sf::Vector2u tile_size;
    uint32_t columns;
    Player *player;



public:

    explicit MapaTMX(const string &archivo, sf::Texture &pl_tx,queue<Enemies*> &enemies) {
        if (!map.load(archivo))
            throw "Cannot open map";

        // Me guardo el tamaño de los tiles
        tile_size.x = map.getTileSize().x;
        tile_size.y = map.getTileSize().y;

        // Me traigo el Tileset que voy a usar y cargo la imagen y veo cuantas columnas tiene.
        const auto &tileSet = map.getTilesets();
        textura.loadFromFile(tileSet[0].getImagePath());
        columns = tileSet[0].getColumnCount();

        // Me traigo las capas
        const auto &layers = map.getLayers();

        for (int i = 0; i < layers.size(); ++i) { // recorro las capas

            // Capa de mosaicos
            if (layers[i]->getType() == tmx::Layer::Type::Tile) {
                const auto &tileLayer = layers[i]->getLayerAs<tmx::TileLayer>();
                const auto &tiles = tileLayer.getTiles(); // Me traigo todos los mosaicos

                int col = 0;
                int fila = 0;
                for (auto tile : tiles) {

                    if (tile.ID != 0) {
                        sprites.push_front(new sf::Sprite(textura)); // Agrego un nuevo sprite a la lista
                        sf::Sprite *sp = sprites.get(0);
                        int tx_fila = (tile.ID - 1) / columns;
                        int tx_col = (tile.ID - 1) % columns;
                        sp->setTextureRect({tx_col * (int) tile_size.x, tx_fila * (int) tile_size.x, (int) tile_size.x,
                                            (int) tile_size.x});
                        sp->setPosition(col * tile_size.x, fila * tile_size.x);
                    }

                    if (++col == map.getTileCount().x) {
                        col = 0;
                        fila++;
                    }
                }
                //capa de Objetos
            } else if (layers[i]->getType() == tmx::Layer::Type::Object) {
                const auto &objectLayer = layers[i]->getLayerAs<tmx::ObjectGroup>();
                const auto &objects = objectLayer.getObjects();
                for (int j = 0; j < objects.size(); ++j) {
                    if (objects[j].getName() == "player") {
                        player = new Player(pl_tx);
                        player->getSprite().setPosition(objects[j].getPosition().x,objects[j].getPosition().y);
                    }
                    if (objects[j].getName() == "zombies") {
                        Enemies *enemy = new Enemies();
                        enemy->getSprite().setPosition(objects[j].getPosition().x, objects[j].getPosition().y);
                        enemy->getSprite().setScale(0.5f, 0.5f);
                        enemy->getSprite().setOrigin((float) enemy->getTexture().getSize().x / 2,
                                                     (float) enemy->getTexture().getSize().y / 2);
                        enemies.push(enemy);
                    }
                }
            }
        }
    }

    void dibujar(sf::RenderWindow &w) {

        for(sprites.iterInit();! sprites.iterEnd(); sprites.iterNext()){
            w.draw(*sprites.iterGet());
        }

    }

    Player *getPlayer() {
        return player;
    }
};


#endif //TESTSFML_MAPATMX_H