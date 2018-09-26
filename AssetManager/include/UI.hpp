#ifndef UI_HPP
#define UI_HPP

#include "core.hpp"
#include "TileMap.hpp"
#include "TextureHolder.hpp"

class UI {
public:
	UI() = delete;
	UI(const UI&) = delete;
	UI(Window *window);

	//Drawing
	void drawEditingWindow();
	void drawSelectedTexture();
	void drawGrid();
	void drawPlacementBox();
	void handleUiInputs(TileMap &map);

	TextureHolder &getTextureHolder();
	sf::Texture &getSelectedTexture();
	sf::Vector2i &getMousePosition();

private:
	void drawEditingWindowMenu();

	Window *m_gameWindow;
	TextureHolder m_textureHolder;
	sf::Texture *m_selectedTexture;
	char m_tempTextureName[128];
	bool m_drawGrid;
	sf::Vector2i m_tilesToPlace;
	sf::Vector2i m_mousePosition;

};

#endif /* UI_HPP */

