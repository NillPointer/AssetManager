#ifndef UI_HPP
#define UI_HPP

#include <nlohmann/json.hpp>
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
	bool &getSaveMap();
	bool &getLoadMap();
	void saveMap(TileMap &map);
	void loadMap(TileMap &map);

private:
	void drawEditingWindowMenu();

	Window *m_gameWindow;
	TextureHolder m_textureHolder;
	sf::Texture *m_selectedTexture;
	bool m_drawGrid;
	bool m_saveMap;
	bool m_loadMap;
	sf::Vector2i m_tilesToPlace;
	sf::Vector2i m_mousePosition;

};

#endif /* UI_HPP */

