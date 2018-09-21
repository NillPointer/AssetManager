#include <math.h>
#include "Game.h"

Game::Game() : m_window("Tiling", sf::Vector2u(800, 600))

{
	m_clock.restart();
	srand(static_cast<unsigned int>(time(nullptr)));

	m_elapsed = 0.0f;
	m_textureHolder.Load("resources/terrain.png", "terrain",{ 32,32 });
}

Game::~Game(){}

sf::Time Game::getElapsed(){ return m_clock.getElapsedTime(); }
void Game::restartClock(){ m_elapsed += m_clock.restart().asSeconds(); }
Window* Game::getWindow(){ return &m_window; }

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
	m_window.GetView()->move(-32.0f * dragDelta);
	m_window.GetRenderWindow()->setView(*m_window.GetView());

	if (ImGui::IsMouseClicked(sf::Mouse::Left) && ImGui::GetMousePos().x > 32 * 6.7f) {
		if (m_selectedTexture == nullptr) return;
		Tile tile(m_selectedTexture);
		auto mousePos = sf::Mouse::getPosition(*m_window.GetRenderWindow());
		sf::Vector2i pos(round(mousePos.x / 32) * 32, round(mousePos.y / 32) * 32);
		sf::Vector2f tilePos = m_window.GetRenderWindow()->mapPixelToCoords(pos);
		tile.setTilePosition(tilePos);
		m_map.add(tile);
	}
}

void Game::update(){
	m_window.Update();
	ImGui::SFML::Update(*m_window.GetRenderWindow(), getElapsed());
	showTileEditing();
}

void Game::render(){
	m_window.BeginDraw();
	// Render here.

	m_window.Draw(m_map);

	sf::VertexArray lines(sf::Lines, 2 * round(ImGui::GetIO().DisplaySize.x / 32));
	int i = 0;
	for (int n = 32; n < ImGui::GetIO().DisplaySize.x; n += 32) {
		lines[i++].position = m_window.GetRenderWindow()->mapPixelToCoords({ n, 0 });
		lines[i++].position = m_window.GetRenderWindow()->mapPixelToCoords({ n, (int)ImGui::GetIO().DisplaySize.y });
	}

	m_window.GetRenderWindow()->draw(lines);

	i = 0;
	lines.clear();
	lines.resize(2 * round(ImGui::GetIO().DisplaySize.y / 32));
	for(int n = 32; n < ImGui::GetIO().DisplaySize.y; n += 32) {
		lines[i++].position = m_window.GetRenderWindow()->mapPixelToCoords({ 0, n });
		lines[i++].position = m_window.GetRenderWindow()->mapPixelToCoords({ (int)ImGui::GetIO().DisplaySize.x, n });
	}

	m_window.GetRenderWindow()->draw(lines);

	ImGui::SFML::Render(*m_window.GetRenderWindow());
	m_window.EndDraw();
}

void Game::showTileEditing() {
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_MenuBar;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	ImGui::SetNextWindowPos(ImVec2(0, 0));
	ImGui::SetNextWindowSize(ImVec2(32 * 6.7f, ImGui::GetIO().DisplaySize.y));

	if (!ImGui::Begin("Tile Editor", nullptr, window_flags)) {
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}

	if (ImGui::BeginMenuBar()) {
		if (ImGui::BeginMenu("Menu")) {
			if (ImGui::MenuItem("Reset View", nullptr, nullptr)) {
				m_window.GetView()->setCenter({ 0,0 });
				m_window.GetRenderWindow()->setView(*m_window.GetView());
			}
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
