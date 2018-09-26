#ifndef GAME_HPP
#define GAME_HPP

#include "core.hpp"
#include "Window.hpp"
#include "UI.hpp"
#include "TileMap.hpp"
#include "AssetManager.hpp"
#include "TextureHolder.hpp"

class Game{
public:
	Game();
	~Game();

	void handleInput();
	void update();
	void render();

	sf::Time getElapsed();
	void restartClock();

	Window *getWindow();
	TileMap *getTileMap();
private:
	Window m_window;
	UI m_ui;
	TileMap m_map;
	sf::Clock m_clock;
	float m_elapsed;
};
#endif /* GAME_HPP */
