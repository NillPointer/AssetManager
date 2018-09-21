#include "TextureHolder.hpp"

TextureHolder::TextureHolder() {}

void TextureHolder::Load(std::string filename, std::string textureName, sf::Vector2u spriteSize) {
	if (!m_Image.loadFromFile(filename))
		return;
	
	auto counter = 0;
	for (unsigned y = 0; y < m_Image.getSize().y; y+=spriteSize.y) {
		for (unsigned x = 0; x < m_Image.getSize().x; x+=spriteSize.x) {
			sf::Texture text;
			text.loadFromImage(m_Image, sf::IntRect(x, y, spriteSize.x, spriteSize.y));
			m_Textures.emplace(textureName + std::to_string(counter++), text);
		}
	}
}

sf::Texture *TextureHolder::GetTexture(std::string const& filename) {
	std::map<std::string, sf::Texture>::iterator it = m_Textures.find(filename);
	if (it == m_Textures.end()) {
		return nullptr;
	}
	return &(it->second);
}

int TextureHolder::getCount() {
	return m_Textures.size();
}