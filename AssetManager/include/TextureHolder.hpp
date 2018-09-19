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
	sf::IntRect *GetTextureRects(std::string const& filename);
	int getCount();
	sf::Texture *GetTexture();

private:
	std::map<std::string, sf::IntRect>m_TextureRects;
	sf::Texture m_Texture;
};


#endif // !TEXTUREHOLDER_HPP

