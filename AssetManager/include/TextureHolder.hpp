#ifndef TEXTUREHOLDER_HPP
#define TEXTUREHOLDER_HPP

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>

class TextureHolder{
public:
	TextureHolder();
	void load(std::string filename, std::string textureName, sf::Vector2u spriteSize);
	std::map<std::string, sf::Texture> &getTextures();
	sf::Texture *getTexture(std::string filename);
	std::vector<std::string> &TextureHolder::getTextureNames();

private:
	std::vector<std::string> m_textureNames;
	std::map<std::string, sf::Texture> m_textures;
};


#endif // !TEXTUREHOLDER_HPP

