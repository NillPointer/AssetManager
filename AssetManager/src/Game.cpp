#include "Game.h"

Game::Game() : m_window("Tiling", sf::Vector2u(800, 600))

{
	m_clock.restart();
	srand(time(nullptr));

	m_elapsed = 0.0f;
	m_TextureHolder.Load("resources/terrain.png", "test",{ 32,32 });
	/*
	if (!map.load("resources/tileset.png", sf::Vector2u(32, 32), level, 16, 8))
		return;
		*/
}

Game::~Game(){}

sf::Time Game::GetElapsed(){ return m_clock.getElapsedTime(); }
void Game::RestartClock(){ m_elapsed += m_clock.restart().asSeconds(); }
Window* Game::GetWindow(){ return &m_window; }

void Game::HandleInput(){
	// Input handling.
	if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up) 
		){
		//scroll up
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down) ){
		//scroll down
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left) ){
		//right
	} else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)){
		//left
	}
}

void Game::Update(){
	m_window.Update();
	ImGui::SFML::Update(*m_window.GetRenderWindow(), GetElapsed());
	ShowTileEditing();
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
	m_window.GetRenderWindow()->draw(this->map);
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

	for (int i = 0; i < m_TextureHolder.getCount(); i++) {
		if (i % (int)(ImGui::GetIO().DisplaySize.x/32 - 9) != 0) ImGui::SameLine();
		ImGui::ImageButton(sf::Sprite(*m_TextureHolder.GetTexture(), *m_TextureHolder.GetTextureRects("test"+std::to_string(i))), 4);
	}
	ImGui::End();
}
