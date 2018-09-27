#include "TextureHolder.hpp"

TextureHolder::TextureHolder() {}

void TextureHolder::load(std::string filename, sf::Vector2u spriteSize) {
	
	auto existsFilename = std::find(m_textureFilenames.begin(), m_textureFilenames.end(), filename);
	if (existsFilename != m_textureFilenames.end()) {
		printf("Filename already loaded\n");
		return;
	}

	sf::Image image;
	if (!image.loadFromFile(filename))
		return;

	auto textureName = splitFilename(filename);
	m_textureFilenames.push_back(filename);

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
			m_textures.emplace(textureName + "." + std::to_string(n), text);
		}
		x += 32;
	}
}

std::map<std::string, sf::Texture> &TextureHolder::getTextures() {
	return m_textures;
}

std::vector<std::string> &TextureHolder::getTextureFilenames() {
	return m_textureFilenames; 
}

std::string TextureHolder::getTextureName(sf::Texture *texture) {
	for (auto &kv : m_textures) if (&kv.second == texture) return kv.first;
	return "NON";
}

sf::Texture *TextureHolder::getTexture(std::string filename) {
	auto it = m_textures.find(filename);
	if (it == m_textures.end()) {
		return nullptr;
	}
	return &(it->second);
}

std::string TextureHolder::splitFilename(std::string &path) {
	std::size_t found = path.find_last_of("/\\");
	return path.substr(found + 1);
}