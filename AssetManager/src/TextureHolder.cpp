#include "TextureHolder.hpp"
#include <stdlib.h>

TextureHolder::TextureHolder() {}

void TextureHolder::Load(std::string filename, std::string textureName, sf::Vector2u spriteSize) {
	if (!m_Texture.loadFromFile(filename))
		return;
	
	auto counter = 0;
	for (int y = 0; y < m_Texture.getSize().y; y+=spriteSize.y) {
		for (int x = 0; x < m_Texture.getSize().x; x+=spriteSize.x) {
			m_TextureRects.emplace(textureName + std::to_string(counter++), sf::IntRect(x,y,spriteSize.x, spriteSize.y));
		}
	}
}

sf::IntRect *TextureHolder::GetTextureRects(std::string const& filename) {
	std::map<std::string, sf::IntRect>::iterator it = m_TextureRects.find(filename);
	if (it == m_TextureRects.end()) {
		return nullptr;
	}
	return &(it->second);
}

sf::Texture *TextureHolder::GetTexture() {
	return &m_Texture;
}

int TextureHolder::getCount() {
	return m_TextureRects.size();
}