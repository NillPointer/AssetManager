#include "Tile.hpp"

Tile::Tile(sf::Texture *texture, sf::Vector2f pos) : m_texture(texture), m_vertices(sf::Quads, 4) {
	m_vertices[0].texCoords = { 0 , 0 };
	m_vertices[1].texCoords = { 32 , 0 };
	m_vertices[2].texCoords = { 32 , 32 };
	m_vertices[3].texCoords = { 0 , 32 };

	setTilePosition(pos);
}

sf::Texture *Tile::getTexture(){
	return m_texture;
}

void Tile::setTexture(sf::Texture *texture) {
	m_texture = texture;
}

void Tile::setTilePosition(const sf::Vector2f& v) {
	m_vertices[0].position = { getPosition().x , getPosition().y };
	m_vertices[1].position = { getPosition().x + 32 , getPosition().y };
	m_vertices[2].position = { getPosition().x + 32 , getPosition().y + 32 };
	m_vertices[3].position = { getPosition().x , getPosition().y + 32 };

	setPosition(v);
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = m_texture;

	// draw the vertex array
	target.draw(m_vertices, states);
}