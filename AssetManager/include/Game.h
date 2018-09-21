#ifndef GAME_HPP
#define GAME_HPP

#include "Window.h"
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

	Window* getWindow();
private:
	void showTileEditing();

	Window m_window;
	sf::Clock m_clock;
	float m_elapsed;
	TileMap m_map;
	TextureHolder m_textureHolder;
	sf::Texture *m_selectedTexture = nullptr;
};
#endif /* GAME_HPP */
