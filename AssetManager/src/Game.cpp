#include <math.h>
#include <nfd.h>
#include "Game.hpp"

Game::Game() : m_window("Tiling", sf::Vector2u(800, 600)) {
	m_clock.restart();
	srand(static_cast<unsigned int>(time(nullptr)));

	m_elapsed = 0.0f;
	m_selectedTexture = nullptr;
	m_drawGrid = true;
	m_tilesToPlace = { 1,1 };
	strcpy_s(m_tempTextureName, "");
}

Game::~Game(){}

sf::Time Game::getElapsed(){ return m_clock.getElapsedTime(); }
void Game::restartClock(){ m_elapsed += m_clock.restart().asSeconds(); }
Window *Game::getWindow(){ return &m_window; }
TextureHolder *Game::getTextureHolder() { return &m_textureHolder; }
void Game::setSelectedTexture(sf::Texture * texture) { m_selectedTexture = texture; }

void Game::handleInput() {
	// Input handling.
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)
		) {
		//scroll up
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
		//scroll down
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
		//right
	} else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		//left
	}

	auto mousePos = sf::Mouse::getPosition(*getWindow()->getRenderWindow());
	m_mousePosition = sf::Vector2i((int)round(mousePos.x / 32) * 32, (int)round(mousePos.y / 32) * 32);

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
		getWindow()->getView()->move(-32.0f * dragDelta);
		getWindow()->resetView();
		return;
	}

	// Placing or removing tiles
	if (ImGui::IsAnyMouseDown() && ImGui::GetMousePos().x > TILE_EDITING_WINDOW_WIDTH) {
		for (int x = 1, right = m_tilesToPlace.x / 2; x <= m_tilesToPlace.x; ++x, --right) {
			for (int y = 1, top = m_tilesToPlace.y / 2; y <= m_tilesToPlace.y; ++y, --top) {
				sf::Vector2i tilePos({ m_mousePosition.x - (right * 32), m_mousePosition.y - (top * 32) });
				if (ImGui::IsMouseClicked(sf::Mouse::Left)) {
					m_map.add(Tile(m_selectedTexture, getWindow()->getRenderWindow()->mapPixelToCoords(tilePos)));
				} else if (ImGui::IsMouseClicked(sf::Mouse::Right)) {
					m_map.remove(getWindow()->getRenderWindow()->mapPixelToCoords(tilePos));
				}
			}
		}
	}
}

void Game::update() {
	getWindow()->update();
	ImGui::SFML::Update(*getWindow()->getRenderWindow(), getElapsed());
}

void Game::render(){
	getWindow()->beginDraw();
	// Render here.
	//ImGui::ShowDemoWindow();

	getWindow()->draw(m_map);
	if (m_drawGrid) drawGrid();
	drawPlacementBox();

	drawTileEditing();
	if (m_selectedTexture != nullptr) drawSelectedTexture();
	ImGui::SFML::Render(*getWindow()->getRenderWindow());
	getWindow()->endDraw();
}

void Game::drawTileEditing() {
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(TILE_EDITING_WINDOW_WIDTH, ImGui::GetIO().DisplaySize.y));

	if (!ImGui::Begin("Tile Editor", nullptr, TILE_EDIT_WINDOW_FLAGS)) {
		ImGui::End();
		return;
	}

	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("Menu")) {
			ImGui::InputText("Name Sprite Set", m_tempTextureName, IM_ARRAYSIZE(m_tempTextureName));
			if (ImGui::MenuItem("Load Spritesheet", nullptr, nullptr)) {
				nfdchar_t *outPath = nullptr;
				nfdresult_t result = NFD_OpenDialog("png,jpg", "", &outPath);
				if (result == NFD_OKAY) {
					m_textureHolder.load(outPath, m_tempTextureName, { 32,32 });
					strcpy_s(m_tempTextureName, "");
					free(outPath);
				}
			}
			ImGui::Separator();
			if (ImGui::MenuItem("Reset View", nullptr, nullptr)) {
				getWindow()->getView()->setCenter({ 0,0 });
				getWindow()->resetView();
			}
			ImGui::Separator();
			ImGui::MenuItem("Draw Grid", nullptr, &m_drawGrid);
			ImGui::Separator();
			ImGui::ColorEdit3("Change Background", getWindow()->getColour(), ImGuiColorEditFlags_Uint8 | ImGuiColorEditFlags_HEX);
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
	
	auto wheel = ImGui::GetIO().MouseWheel;
	if (m_tilesToPlace.x + wheel > 0) m_tilesToPlace.x += (int)wheel;
	if (m_tilesToPlace.y + wheel > 0) m_tilesToPlace.y += (int)wheel;

	auto counter = 0;
	for (auto &texture : m_textureHolder.getTextures()) {
		if (counter % 3 != 0) ImGui::SameLine();
		ImGui::PushID(counter++);
		if (ImGui::ImageButton(texture.second, { 32,32 })) m_selectedTexture = &texture.second;
		ImGui::PopID();
	}

	ImGui::End();
}

void Game::drawGrid() {
	sf::VertexArray lines(sf::Lines, ((int)ImGui::GetIO().DisplaySize.x + (int)ImGui::GetIO().DisplaySize.x)/16);
	int i = 0;
	for (int x = (int)(TILE_EDITING_WINDOW_WIDTH/32) * 32; x < ImGui::GetIO().DisplaySize.x; x += 32) {
		lines[i].position = getWindow()->getRenderWindow()->mapPixelToCoords({ x, 0 });
		lines[i++].color = sf::Color(255, 255, 255, 50);
		lines[i].position = getWindow()->getRenderWindow()->mapPixelToCoords({ x, (int)ImGui::GetIO().DisplaySize.y });
		lines[i++].color = sf::Color(255, 255, 255, 50);
	}
	for (int n = 32; n < ImGui::GetIO().DisplaySize.y; n += 32) {
		lines[i].position = getWindow()->getRenderWindow()->mapPixelToCoords({ 0, n });
		lines[i++].color = sf::Color(255, 255, 255, 50);
		lines[i].position = getWindow()->getRenderWindow()->mapPixelToCoords({ (int)ImGui::GetIO().DisplaySize.x, n });
		lines[i++].color = sf::Color(255, 255, 255, 50);
	}
	getWindow()->getRenderWindow()->draw(lines);
}

void Game::drawPlacementBox() {
	sf::VertexArray box(sf::Quads, 4);
	box[0].position = getWindow()->getRenderWindow()->mapPixelToCoords({ m_mousePosition.x - (m_tilesToPlace.x / 2 * 32), m_mousePosition.y - (m_tilesToPlace.y / 2 * 32) });
	box[1].position = getWindow()->getRenderWindow()->mapPixelToCoords({ m_mousePosition.x + ((m_tilesToPlace.x + 1) / 2 * 32), m_mousePosition.y - (m_tilesToPlace.y / 2 * 32) });
	box[2].position = getWindow()->getRenderWindow()->mapPixelToCoords({ m_mousePosition.x + ((m_tilesToPlace.x + 1) / 2 * 32), m_mousePosition.y + ((m_tilesToPlace.y + 1) / 2 * 32) });
	box[3].position = getWindow()->getRenderWindow()->mapPixelToCoords({ m_mousePosition.x - (m_tilesToPlace.x / 2 * 32), m_mousePosition.y + ((m_tilesToPlace.y + 1) / 2 * 32) });
	for (int i = 0; i < 4; ++i) box[i].color = sf::Color(255, 255, 255, 100);
	getWindow()->draw(box);
}

void Game::drawSelectedTexture() {
	ImGui::SetNextWindowPos(ImVec2(ImGui::GetIO().DisplaySize.x - 60, 0));
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, 60));
	ImGui::SetNextWindowBgAlpha(0.5f);
	if (!ImGui::Begin("Selected Texture", nullptr, SELECTED_TEXTURE_WINDOW_FLAGS)) {
		ImGui::End();
		return;
	}

	ImGui::Image(*m_selectedTexture, { 45,45 }, sf::Color::White, sf::Color::Red);

	ImGui::End();
}