#pragma once
#include <map>

#include <SFML/Graphics.hpp>

namespace GameDevCpp {
    class AssetManager
    {
    public:
        AssetManager(){}
        ~AssetManager(){}
        void loadTexture(std::string name, std::string fileName);
        sf::Texture &GetTexture(std::string name);
        
        void loadFont(std::string name, std::string fileName);
        sf::Font &GetFont(std::string name);
        
        private:
        
            std::map<std::string, sf::Texture> textures_;
            std::map<std::string, sf::Font> fonts_;
        
        
    };

    
}
