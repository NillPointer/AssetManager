#include "Game.h"

Game::Game() : m_window("Tiling", sf::Vector2u(800, 600)), m_Vertices(sf::Quads, 32 * 32 * 4)

{
	m_clock.restart();
	srand(time(nullptr));

	m_elapsed = 0.0f;
	m_TextureHolder.Load("resources/terrain.png", "terrain",{ 32,32 });
	/*
	if (!map.load("resources/tileset.png", sf::Vector2u(32, 32), level, 16, 8))
		return;
		*/
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

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		if (m_SelectedTexture == nullptr) return;
		sf::Sprite s;
		s.setTexture(*m_SelectedTexture);
		s.setPosition({ (float)sf::Mouse::getPosition().x, (float)sf::Mouse::getPosition().y });
		map.push_back(s);
		/*sf::Vector2i m = sf::Mouse::getPosition(*m_window.GetRenderWindow());
		m_Vertices[i++].position = sf::Vector2f(m.x, m.y);
		m_Vertices[i++].position = sf::Vector2f(m.x + 32, m.y);
		m_Vertices[i++].position = sf::Vector2f(m.x + 32, m.y + 32);
		m_Vertices[i++].position = sf::Vector2f(m.x, m.y + 32);

		m_Vertices[j++].texCoords = { 0, 0 };
		m_Vertices[j++].texCoords = { 32, 0 };
		m_Vertices[j++].texCoords = { 32, 32 };
		m_Vertices[j++].texCoords = { 0, 32 };*/
	}
}

void Game::Update(){
	m_window.Update();
	ImGui::SFML::Update(*m_window.GetRenderWindow(), GetElapsed());
	ShowTileEditing();
	HandleInput();
//    float timestep = 1.0f / m_snake.GetSpeed();
//    if(m_elapsed >= timestep){
//
//
//        m_elapsed -= timestep;
//
//    }
}

void Game::Render(){
	m_window.BeginDraw();
	// Render here.
	//m_window.GetRenderWindow()->draw(this->map);

	for (auto s : map)
		m_window.GetRenderWindow()->draw(s);
	/*if (m_SelectedTexture != nullptr)
		m_window.GetRenderWindow()->draw(m_Vertices, m_SelectedTexture);
	else
		m_window.GetRenderWindow()->draw(m_Vertices);*/

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
		auto s = m_TextureHolder.GetTexture("terrain" + std::to_string(i));
		if (i % n != 0) ImGui::SameLine();
		ImGui::PushID(i);
		bool a = ImGui::ImageButton(*s, { 32,32 });
		if (a) {
			m_SelectedTexture = s;
		}
		ImGui::PopID();
	}
	ImGui::End();
}
