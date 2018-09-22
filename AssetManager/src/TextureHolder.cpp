#include "TextureHolder.hpp"

TextureHolder::TextureHolder() {}

void TextureHolder::load(std::string filename, std::string textureName, sf::Vector2u spriteSize) {
	
	if (textureName.empty()) {
		printf("Name is empty\n");
		return;
	}

	auto exists = std::find(m_textureNames.begin(), m_textureNames.end(), textureName);
	if (exists != m_textureNames.end()) {
		printf("Name already exists\n");
		return;
	}

	sf::Image image;
	if (!image.loadFromFile(filename))
		return;

	m_textureNames.push_back(textureName);

	for (unsigned x = 0, y = 0, n = 0; n < (image.getSize().x/spriteSize.x) * (image.getSize().y/spriteSize.y); ++n) {
		if (x >= image.getSize().x) {
			x = 0;
			y += spriteSize.y;
		}
		sf::Color temp = image.getPixel(x,y);
		bool skip = true;
		for (unsigned u = x+1, v = y, pixelNum = 0; pixelNum < spriteSize.x; ++pixelNum) {
			if (u >= x+spriteSize.x) {
				u = x;
				v++;
			}
			if (temp != image.getPixel(u, v)) {
				skip = false;
				break;
			}
			u++;
		}
		if (!skip) {
			sf::Texture text;
			text.loadFromImage(image, sf::IntRect(x, y, spriteSize.x, spriteSize.y));
			m_textures.emplace(textureName + std::to_string(n), text);
		}
		x += 32;
	}
}

std::map<std::string, sf::Texture> &TextureHolder::getTextures() {
	return m_textures;
}

sf::Texture *TextureHolder::getTexture(std::string filename) {
	auto it = m_textures.find(filename);
	if (it == m_textures.end()) {
		return nullptr;
	}
	return &(it->second);
}

std::vector<std::string> &TextureHolder::getTextureNames() {
	return m_textureNames;
}