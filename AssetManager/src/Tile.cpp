#include "Tile.hpp"

Tile::Tile(sf::Texture *texture) : m_Texture(texture), m_Vertices(sf::Quads, 4) {
	m_Vertices[0].texCoords = { 0 , 0 };
	m_Vertices[1].texCoords = { 32 , 0 };
	m_Vertices[2].texCoords = { 32 , 32 };
	m_Vertices[3].texCoords = { 0 , 32 };
}

sf::Texture *Tile::getTexture(){
	return m_Texture;
}

void Tile::setTexture(sf::Texture *texture) {
	m_Texture = texture;
}

void Tile::setTilePosition(const sf::Vector2f& v) {
	m_Vertices[0].position = { getPosition().x , getPosition().y };
	m_Vertices[1].position = { getPosition().x + 32 , getPosition().y };
	m_Vertices[2].position = { getPosition().x + 32 , getPosition().y + 32 };
	m_Vertices[3].position = { getPosition().x , getPosition().y + 32 };

	setPosition(v);
}

void Tile::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	// apply the transform
	states.transform *= getTransform();

	// apply the tileset texture
	states.texture = m_Texture;

	// draw the vertex array
	target.draw(m_Vertices, states);
}