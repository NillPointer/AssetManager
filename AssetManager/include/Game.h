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

	void HandleInput();
	void Update();
	void Render();

	sf::Time GetElapsed();
	void RestartClock();

	Window* GetWindow();
private:
	void ShowTileEditing();

	Window m_window;
	sf::Clock m_clock;
	float m_elapsed;
	TileMap m_Map;
	TextureHolder m_TextureHolder;
	sf::Texture *m_SelectedTexture = nullptr;
};
#endif /* GAME_HPP */
