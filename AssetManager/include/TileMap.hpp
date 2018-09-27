#ifndef TILEMAP_HPP
#define TILEMAP_HPP

#include <list>
#include "Tile.hpp"

class TileMap : public sf::Drawable
{
public:
	void add(Tile tile);
	void remove(const sf::Vector2f &tilePos);
	std::list<Tile> &getMap();
private:
	virtual void draw(sf::RenderTarget & target, sf::RenderStates states) const;
	std::list<Tile> m_map;
};
#endif /* TILEMAP_HPP */
