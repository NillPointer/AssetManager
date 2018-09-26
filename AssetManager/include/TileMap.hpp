#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <list>
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
	void remove(const sf::Vector2f &tilePos);
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	std::list<Tile> m_map;
};
#endif /* TILEMAP_HPP */
