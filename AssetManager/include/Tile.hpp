#ifndef TILE_HPP
#define TILE_HPP

#include "Window.hpp"
#include <string>

class Tile : public sf::Drawable, public sf::Transformable {
public:
	Tile(sf::Texture *texture, sf::Vector2f pos);
	Tile(sf::Texture *texture) : Tile(texture, { 0,0 }) {};
	sf::Texture &getTexture();
	void setTexture(sf::Texture *texture);
	void setTilePosition(const sf::Vector2f& v);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture *m_texture = nullptr;
	std::string *m_textureName;
};

#endif // !TILE_HPP

