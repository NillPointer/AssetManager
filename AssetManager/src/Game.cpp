#include <math.h>
#include "Game.h"

Game::Game() : m_window("Tiling", sf::Vector2u(800, 600))

{
	m_clock.restart();
	srand(static_cast<unsigned int>(time(nullptr)));

	m_elapsed = 0.0f;
	m_TextureHolder.Load("resources/terrain.png", "terrain",{ 32,32 });
}

Game::~Game(){}

sf::Time Game::GetElapsed(){ return m_clock.getElapsedTime(); }
void Game::RestartClock(){ m_elapsed += m_clock.restart().asSeconds(); }
Window* Game::GetWindow(){ return &m_window; }

void Game::HandleInput() {
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

	if (ImGui::IsMouseClicked(sf::Mouse::Left) && ImGui::GetMousePos().y < 300) {
		auto pos = sf::Mouse::getPosition(*m_window.GetRenderWindow());
		if (m_SelectedTexture == nullptr) return;
		Tile tile(m_SelectedTexture);
		auto x = round(pos.x / 32) * 32;
		auto y = round(pos.y / 32) * 32;
		tile.setTilePosition(sf::Vector2f(x, y));
		m_Map.add(tile);
	}
}

void Game::Update(){
	m_window.Update();
	ImGui::SFML::Update(*m_window.GetRenderWindow(), GetElapsed());
	ShowTileEditing();
}

void Game::Render(){
	m_window.BeginDraw();
	// Render here.

	m_window.Draw(m_Map);

	sf::VertexArray lines(sf::Lines, 2 * round(ImGui::GetIO().DisplaySize.x / 32));
	int i = 0;
	for (int n = 32; n < ImGui::GetIO().DisplaySize.x; n += 32) {
		lines[i++].position = { (float)n, 0 };
		lines[i++].position = { (float)n, ImGui::GetIO().DisplaySize.y };
	}

	m_window.GetRenderWindow()->draw(lines);

	i = 0;
	lines.clear();
	lines.resize(2 * round(ImGui::GetIO().DisplaySize.y / 32));
	for(int n = 32; n < ImGui::GetIO().DisplaySize.y; n += 32) {
		lines[i++].position = { 0, (float)n };
		lines[i++].position = { ImGui::GetIO().DisplaySize.x, (float)n };
	}

	m_window.GetRenderWindow()->draw(lines);

	ImGui::SFML::Render(*m_window.GetRenderWindow());
	m_window.EndDraw();
}

void Game::ShowTileEditing() {
	ImGuiWindowFlags window_flags = 0;
	window_flags |= ImGuiWindowFlags_NoMove;
	window_flags |= ImGuiWindowFlags_NoResize;
	window_flags |= ImGuiWindowFlags_NoCollapse;

	ImGui::SetNextWindowPos(ImVec2(0, ImGui::GetIO().DisplaySize.y - ImGui::GetIO().DisplaySize.y/2.5f));
	ImGui::SetNextWindowSize(ImVec2(ImGui::GetIO().DisplaySize.x, ImGui::GetIO().DisplaySize.y / 2.5f));

	if (!ImGui::Begin("Tile Editor", nullptr, window_flags)) {
		// Early out if the window is collapsed, as an optimization.
		ImGui::End();
		return;
	}
	
	auto n = (int)(ImGui::GetIO().DisplaySize.x / 32) - 9;
	for (int i = 0; i < m_TextureHolder.getCount(); i++) {
		auto tex = m_TextureHolder.GetTexture("terrain" + std::to_string(i));
		if (i % n != 0) ImGui::SameLine();
		ImGui::PushID(i);
		if (ImGui::ImageButton(*tex, { 32,32 })) m_SelectedTexture = tex;
		ImGui::PopID();
	}
	ImGui::End();
}
