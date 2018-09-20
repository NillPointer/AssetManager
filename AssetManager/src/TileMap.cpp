#include "TileMap.hpp"

void TileMap::add(Tile tile) {
	m_Map.push_back(tile);
}

int TileMap::size() {
	return m_Map.size();
}

void TileMap::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	for (auto &kv : m_Map)
		target.draw(kv);
}
