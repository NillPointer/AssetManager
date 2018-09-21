#ifndef TILE_HPP
#define TILE_HPP

#include "Window.h"
#include <string>

class Tile : public sf::Drawable, public sf::Transformable {
public:
	Tile(sf::Texture *texture);
	sf::Texture *getTexture();
	void setTexture(sf::Texture *texture);
	void setTilePosition(const sf::Vector2f& v);

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	sf::VertexArray m_vertices;
	sf::Texture *m_texture = nullptr;
};

#endif // !TILE_HPP

