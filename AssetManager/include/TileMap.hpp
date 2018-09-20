#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <string>
#include <vector>
#include "Tile.hpp"

struct VectorComparator {
	bool operator() (sf::Vector2f lhs, sf::Vector2f rhs) const {
		return lhs.x + lhs.y < rhs.x + rhs.y;
	}
};

class TileMap : public sf::Drawable
{
public:
	void add(Tile tile);
	int size();
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	std::vector<Tile> m_Map;
};
#endif /* TILEMAP_HPP */
