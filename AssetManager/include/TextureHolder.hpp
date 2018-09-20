#ifndef TEXTUREHOLDER_HPP
#define TEXTUREHOLDER_HPP

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Image.hpp>

class TextureHolder{
public:
	TextureHolder();
	void Load(std::string filename, std::string textureName, sf::Vector2u spriteSize);
	sf::Texture *GetTexture(std::string const& filename);
	int getCount();

private:
	std::map<std::string, sf::Texture> m_Textures;
	sf::Image m_Image;
};


#endif // !TEXTUREHOLDER_HPP

