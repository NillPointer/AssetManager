#ifndef TEXTUREHOLDER_HPP
#define TEXTUREHOLDER_HPP

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>

class TextureHolder{
public:
	TextureHolder();
	void load(std::string filename, sf::Vector2u spriteSize);
	std::map<std::string, sf::Texture> &getTextures();
	sf::Texture *getTexture(std::string filename);
	std::string getTextureName(sf::Texture *texture);
	std::vector<std::string> &getTextureFilenames();

private:
	std::string splitFilename(std::string &path);

	std::vector<std::string> m_textureFilenames;
	std::map<std::string, sf::Texture> m_textures;
};


#endif // !TEXTUREHOLDER_HPP

