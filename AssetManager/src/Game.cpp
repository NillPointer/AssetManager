#include <math.h>
#include "Game.hpp"

Game::Game() : m_window("Tiling", sf::Vector2u(800, 600)) {
	m_clock.restart();
	srand(static_cast<unsigned int>(time(nullptr)));

	m_elapsed = 0.0f;
	m_selectedTexture = nullptr;
	m_drawGrid = true;
	m_textureHolder.Load("resources/terrain.png", "terrain",{ 32,32 });
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

	if (ImGui::IsMouseClicked(sf::Mouse::Left) && ImGui::GetMousePos().x > 32 * 6.7f) {
		if (m_selectedTexture == nullptr) return;
		Tile tile(m_selectedTexture);
		auto mousePos = sf::Mouse::getPosition(*getWindow()->getRenderWindow());
		sf::Vector2i pos((int)round(mousePos.x / 32) * 32, (int)round(mousePos.y / 32) * 32);
		sf::Vector2f tilePos = getWindow()->getRenderWindow()->mapPixelToCoords(pos);
		tile.setTilePosition(tilePos);
		m_map.add(tile);
	} else if (ImGui::IsMouseClicked(sf::Mouse::Right) && ImGui::GetMousePos().x > 32 * 6.7f) {
		auto mousePos = sf::Mouse::getPosition(*getWindow()->getRenderWindow());
		sf::Vector2i pos((int)round(mousePos.x / 32) * 32, (int)round(mousePos.y / 32) * 32);
		sf::Vector2f tilePos = getWindow()->getRenderWindow()->mapPixelToCoords(pos);
		m_map.remove(tilePos);
		m_selectedTexture = nullptr;
	}
}

void Game::update() {
	getWindow()->update();
	ImGui::SFML::Update(*getWindow()->getRenderWindow(), getElapsed());
	showTileEditing();
}

void Game::render(){
	getWindow()->beginDraw();
	// Render here.
	ImGui::ShowDemoWindow();

	getWindow()->draw(m_map);

	if (m_drawGrid) drawGrid();

	ImGui::SFML::Render(*getWindow()->getRenderWindow());
	getWindow()->endDraw();
}

void Game::showTileEditing() {
	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(TILE_EDITING_WINDOW_WIDTH, ImGui::GetIO().DisplaySize.y));

	if (!ImGui::Begin("Tile Editor", nullptr, TILE_EDIT_WINDOW_FLAGS)) {
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("Menu")) {
			if (ImGui::MenuItem("Reset View", nullptr, nullptr)) {
				getWindow()->getView()->setCenter({ 0,0 });
				getWindow()->resetView();
			}
			ImGui::MenuItem("Draw Grid", nullptr, &m_drawGrid);
			ImGui::ColorEdit3("Change Background", getWindow()->getColour(), ImGuiColorEditFlags_HEX | ImGuiColorEditFlags_Uint8);
			printf("%f %f %f\n", getWindow()->getColour()[0], getWindow()->getColour()[1], getWindow()->getColour()[2]);
			ImGui::EndMenu();
		}
		ImGui::EndMenuBar();
	}
	
	for (int i = 0; i < m_textureHolder.getCount(); i++) {
		auto tex = m_textureHolder.GetTexture("terrain" + std::to_string(i));
		if (i % 4 != 0) ImGui::SameLine();
		ImGui::PushID(i);
		if (ImGui::ImageButton(*tex, { 32,32 })) m_selectedTexture = tex;
		ImGui::PopID();
	}
	ImGui::End();
}

void Game::drawGrid() {
	sf::VertexArray lines(sf::Lines, 2 * (int)round(ImGui::GetIO().DisplaySize.x / 32));
	int i = 0;
	for (int n = 0; n < ImGui::GetIO().DisplaySize.x; n += 32) {
		lines[i++].position = getWindow()->getRenderWindow()->mapPixelToCoords({ n, 0 });
		lines[i++].position = getWindow()->getRenderWindow()->mapPixelToCoords({ n, (int)ImGui::GetIO().DisplaySize.y });
	}

	getWindow()->getRenderWindow()->draw(lines);

	i = 0;
	lines.clear();
	lines.resize(2 * (int)round(ImGui::GetIO().DisplaySize.y / 32));
	for (int n = 32; n < ImGui::GetIO().DisplaySize.y; n += 32) {
		lines[i++].position = getWindow()->getRenderWindow()->mapPixelToCoords({ 0, n });
		lines[i++].position = getWindow()->getRenderWindow()->mapPixelToCoords({ (int)ImGui::GetIO().DisplaySize.x, n });
	}

	getWindow()->getRenderWindow()->draw(lines);
}