#include "Game.h"

Game::Game() : m_window("Tiling", sf::Vector2u(1280, 800))

{
	m_clock.restart();
	srand(time(nullptr));
    //mapSprite_ = nullptr;

	m_elapsed = 0.0f;
	if (!map.load(//resourcePath()+//"terrain.png",
		"resources/tileset.png", sf::Vector2u(32, 32), level, 16, 8))
		// return -1;
		return;
  //  else
       // mapSprite_=new sf::Sprite(map)
	
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

	m_window.EndDraw();
}
