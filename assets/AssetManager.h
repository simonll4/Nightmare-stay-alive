#ifndef MAIN_CPP_ASSETMANAGER_H
#define MAIN_CPP_ASSETMANAGER_H

#include <SFML/Graphics.hpp>
#include <map>

class AssetManager{

public:
    AssetManager();

    static sf::Texture& GetTexture(std::string const& filename);

private:
    std::map<std::string, sf::Texture> m_Textures;

    static AssetManager* sInstance;

};

#endif //MAIN_CPP_ASSETMANAGER_H
