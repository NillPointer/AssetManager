#include <math.h>
#include "Game.hpp"

Game::Game() : m_window("Tiling", sf::Vector2u(800, 600)), m_ui(&m_window){
	m_clock.restart();
	srand(static_cast<unsigned int>(time(nullptr)));
	m_elapsed = 0.0f;
}

Game::~Game() { }

sf::Time Game::getElapsed(){ return m_clock.getElapsedTime(); }
void Game::restartClock(){ m_elapsed += m_clock.restart().asSeconds(); }
Window *Game::getWindow(){ return &m_window; }
TileMap *Game::getTileMap() { return &m_map; }

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

	m_ui.handleUiInputs(m_map);
}

void Game::update() {
	getWindow()->update();
	ImGui::SFML::Update(*getWindow()->getRenderWindow(), getElapsed());
	checkLoadingMap();
	checkSavingMap();
}

void Game::render(){
	getWindow()->beginDraw();

	// Draw map
	getWindow()->draw(m_map);

	// Drawing UI
	m_ui.drawEditingWindow();
	m_ui.drawGrid();
	m_ui.drawPlacementBox();
	m_ui.drawSelectedTexture();

	ImGui::SFML::Render(*getWindow()->getRenderWindow());
	getWindow()->endDraw();
}

void Game::checkSavingMap() {
	if (!m_ui.getSaveMap()) return;

	m_ui.saveMap(m_map);
}

void Game::checkLoadingMap() {
	if (!m_ui.getLoadMap()) return;

	m_ui.loadMap(m_map);
}