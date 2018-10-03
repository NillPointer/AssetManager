#include <fstream>
#include <iostream>
#include <nfd.h>
#include "UI.hpp"

UI::UI(Window *window) : m_gameWindow(window), m_drawGrid(true), m_tilesToPlace({ 1,1 }), m_mousePosition({ 0,0 }), m_saveMap(false)
{}

TextureHolder &UI::getTextureHolder() { return m_textureHolder; }
sf::Texture &UI::getSelectedTexture() { return *m_selectedTexture; }
sf::Vector2i &UI::getMousePosition() { return m_mousePosition; }
bool &UI::getSaveMap() { return m_saveMap; }
bool &UI::getLoadMap() { return m_loadMap; }

void UI::drawEditingWindow() {
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(TILE_EDITING_WINDOW_WIDTH, ImGui::GetIO().DisplaySize.y));

	if (!ImGui::Begin("Tile Editor", nullptr, TILE_EDIT_WINDOW_FLAGS)) {
		ImGui::End();
		return;
	}

	drawEditingWindowMenu();

	if (m_mousePosition.x > TILE_EDITING_WINDOW_WIDTH) {
		auto wheel = ImGui::GetIO().MouseWheel;
		if (m_tilesToPlace.x + wheel > 0) m_tilesToPlace.x += (int)wheel;
		if (m_tilesToPlace.y + wheel > 0) m_tilesToPlace.y += (int)wheel;
	}

	auto counter = 0;
	for (auto &texture : m_textureHolder.getTextures()) {
		if (counter % 3 != 0) ImGui::SameLine();
		ImGui::PushID(counter++);
		if (ImGui::ImageButton(texture.second, { 32,32 })) m_selectedTexture = &texture.second;
		ImGui::PopID();
	}

	ImGui::End();
}

void UI::drawEditingWindowMenu() {
	if (m_gameWindow == nullptr) return;
	auto mousePos = ImGui::GetMousePos();
	m_mousePosition = sf::Vector2i((int)round(mousePos.x / 32) * 32, (int)round(mousePos.y / 32) * 32);

	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("Menu")) {
			if (ImGui::MenuItem("Load Spritesheet", nullptr, nullptr)) {
				nfdchar_t *outPath = nullptr;
				nfdresult_t result = NFD_OpenDialog("png,jpg", "", &outPath);
				if (result == NFD_OKAY) {
					m_textureHolder.load(outPath, { 32,32 });
					free(outPath);
				}
			}
			ImGui::Separator();
			ImGui::MenuItem("Save Map", nullptr, &m_saveMap, !m_saveMap);
			ImGui::Separator();
			ImGui::MenuItem("Load Map", nullptr, &m_loadMap, !m_loadMap);
			ImGui::Separator();
			if (ImGui::MenuItem("Reset View", nullptr, nullptr)) {
				m_gameWindow->getView()->setCenter({ 0,0 });
				m_gameWindow->resetView();
			}
			ImGui::Separator();
			ImGui::MenuItem("Draw Grid", nullptr, &m_drawGrid);
			ImGui::Separator();
			ImGui::ColorEdit3("Change Background", m_gameWindow->getColour(), ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_HEX);
			ImGui::Separator();
			ImGui::Text("Tiles To Place:");
			ImGui::InputInt("Rows", &m_tilesToPlace.x);
			if (m_tilesToPlace.x < 1) m_tilesToPlace.x = 1;
			ImGui::InputInt("Columns", &m_tilesToPlace.y);
			if (m_tilesToPlace.y < 1) m_tilesToPlace.y = 1;
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
}

void UI::drawGrid() {
	if (m_gameWindow == nullptr || !m_drawGrid) return;
	sf::VertexArray lines(sf::Lines, ((int)ImGui::GetIO().DisplaySize.x + (int)ImGui::GetIO().DisplaySize.x) / 16);
	int i = 0;
	for (int x = (int)(TILE_EDITING_WINDOW_WIDTH / 32) * 32; x < ImGui::GetIO().DisplaySize.x; x += 32) {
		lines[i].position = m_gameWindow->getRenderWindow()->mapPixelToCoords({ x, 0 });
		lines[i++].color = sf::Color(255, 255, 255, 50);
		lines[i].position = m_gameWindow->getRenderWindow()->mapPixelToCoords({ x, (int)ImGui::GetIO().DisplaySize.y });
		lines[i++].color = sf::Color(255, 255, 255, 50);
	}
	for (int n = 32; n < ImGui::GetIO().DisplaySize.y; n += 32) {
		lines[i].position = m_gameWindow->getRenderWindow()->mapPixelToCoords({ 0, n });
		lines[i++].color = sf::Color(255, 255, 255, 50);
		lines[i].position = m_gameWindow->getRenderWindow()->mapPixelToCoords({ (int)ImGui::GetIO().DisplaySize.x, n });
		lines[i++].color = sf::Color(255, 255, 255, 50);
	}
	m_gameWindow->draw(lines);
}

void UI::drawPlacementBox() {
	if (m_gameWindow == nullptr) return;
	sf::VertexArray box(sf::Quads, 4);
	box[0].position = m_gameWindow->getRenderWindow()->mapPixelToCoords({ m_mousePosition.x - (m_tilesToPlace.x / 2 * 32), m_mousePosition.y - (m_tilesToPlace.y / 2 * 32) });
	box[1].position = m_gameWindow->getRenderWindow()->mapPixelToCoords({ m_mousePosition.x + ((m_tilesToPlace.x + 1) / 2 * 32), m_mousePosition.y - (m_tilesToPlace.y / 2 * 32) });
	box[2].position = m_gameWindow->getRenderWindow()->mapPixelToCoords({ m_mousePosition.x + ((m_tilesToPlace.x + 1) / 2 * 32), m_mousePosition.y + ((m_tilesToPlace.y + 1) / 2 * 32) });
	box[3].position = m_gameWindow->getRenderWindow()->mapPixelToCoords({ m_mousePosition.x - (m_tilesToPlace.x / 2 * 32), m_mousePosition.y + ((m_tilesToPlace.y + 1) / 2 * 32) });
	for (int i = 0; i < 4; ++i) box[i].color = sf::Color(255, 255, 255, 100);
	m_gameWindow->draw(box);
}

void UI::drawSelectedTexture() {
	if (!m_selectedTexture) return;
	ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 60, 0));
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 60));
	ImGui::SetNextWindowBgAlpha(0.5f);
	if (!ImGui::Begin("Selected Texture", nullptr, SELECTED_TEXTURE_WINDOW_FLAGS)) {
		ImGui::End();
		return;
	}

	ImGui::Image(*m_selectedTexture, { 45,45 });

	ImGui::End();
}

void UI::handleUiInputs(TileMap &map) {
	if (m_gameWindow == nullptr) return;

	// Moving around the world with middle mouse button
	if (ImGui::IsMouseDown(sf::Mouse::Button::Middle)) {
		sf::Vector2f dragDelta(ImGui::GetMouseDragDelta(sf::Mouse::Middle, 75));
		if (abs(dragDelta.x) > abs(dragDelta.y)) {
			dragDelta.y = 0;
			if (dragDelta.x > 0) dragDelta.x = 1;
			else if (dragDelta.x < 0) dragDelta.x = -1;
			else dragDelta.x = 0;
		} else {
			dragDelta.x = 0;
			if (dragDelta.y > 0) dragDelta.y = 1;
			else if (dragDelta.y < 0) dragDelta.y = -1;
			else dragDelta.y = 0;
		}
		m_gameWindow->getView()->move(-32.0f * dragDelta);
		m_gameWindow->resetView();
		return;
	}

	// Placing or removing tiles
	if (ImGui::IsAnyMouseDown() && ImGui::GetMousePos().x > TILE_EDITING_WINDOW_WIDTH) {
		for (int x = 1, right = m_tilesToPlace.x / 2; x <= m_tilesToPlace.x; ++x, --right) {
			for (int y = 1, top = m_tilesToPlace.y / 2; y <= m_tilesToPlace.y; ++y, --top) {
				sf::Vector2i tilePos({ m_mousePosition.x - (right * 32), m_mousePosition.y - (top * 32) });
				if (ImGui::IsMouseClicked(sf::Mouse::Left)) {
					map.add(Tile(m_selectedTexture, m_gameWindow->getRenderWindow()->mapPixelToCoords(tilePos)));
				} else if (ImGui::IsMouseClicked(sf::Mouse::Right)) {
					map.remove(m_gameWindow->getRenderWindow()->mapPixelToCoords(tilePos));
				}
			}
		}
	}
}

void UI::saveMap(TileMap &map) {
	std::ofstream mapFile;
	nfdchar_t *outPath = nullptr;

	nlohmann::json jsonMap;

	for (Tile &tile : map.getMap()) {
		auto textureName = m_textureHolder.getTextureName(&tile.getTexture());
		jsonMap["Map"] += { textureName, tile.getPosition().x, tile.getPosition().y };
	}

	jsonMap["Textures"] = m_textureHolder.getTextureFilenames();

	nfdresult_t result = NFD_SaveDialog("json", "", &outPath);
	if (result != NFD_OKAY) {
		free(outPath);
		printf("Failed To Save\n");
		return;
	}
	mapFile.open(outPath);

	mapFile << jsonMap.dump(4);

	mapFile.close();
	free(outPath);
	m_saveMap = false;
}

void UI::loadMap(TileMap &map) {
	std::ifstream mapFile;
	std::string mapString;
	nfdchar_t *outPath = nullptr;
	nlohmann::json jsonMap;

	nfdresult_t result = NFD_OpenDialog("json", "", &outPath);
	if (result != NFD_OKAY) {
		free(outPath);
		printf("Failed To Load Map\n");
		return;
	}
	mapFile.open(outPath);

	mapFile.seekg(0, std::ios::end);
	mapString.reserve(mapFile.tellg());
	mapFile.seekg(0, std::ios::beg);
	mapString.assign((std::istreambuf_iterator<char>(mapFile)), std::istreambuf_iterator<char>());
	mapFile.close();
	free(outPath);

	jsonMap = nlohmann::json::parse(mapString);

	for(std::string textureFileName : jsonMap["Textures"]) {
		m_textureHolder.load(textureFileName, { 32,32 });
	}

	for (auto &tile : jsonMap["Map"]) {
		map.add(Tile(m_textureHolder.getTexture(tile[0]), { tile[1], tile[2] }));
	}

	m_loadMap = false;
}