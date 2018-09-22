#include "Window.hpp"


Window::Window(){ setup("Window", sf::Vector2u(640, 480)); }
Window::Window(const std::string& title, const sf::Vector2u& size){ setup(title, size); }
Window::~Window(){ destroy(); }

void Window::setup(const std::string title, const sf::Vector2u& size){
	m_windowTitle = title;
	m_windowSize = size;
	m_isFullscreen = false;
	m_isDone = false;
	create();
}

void Window::create(){
	auto style = (m_isFullscreen ? sf::Style::Fullscreen
		: sf::Style::Default);
	m_window.create({ m_windowSize.x, m_windowSize.y, 32 },
		m_windowTitle, style);
	m_view = m_window.getDefaultView();
	m_view.setCenter({ 0,0 });
	m_window.setView(m_view);
	ImGui::SFML::Init(m_window);
}

void Window::destroy(){
	m_window.close();
}

void Window::beginDraw(){
	m_window.clear(sf::Color(m_backgroundColour[0] * 255, m_backgroundColour[1] * 255, m_backgroundColour[2] * 255,0)); 
}
void Window::endDraw(){ m_window.display(); }

bool Window::isDone(){ return m_isDone; }
bool Window::isFullscreen(){ return m_isFullscreen; }

sf::RenderWindow *Window::getRenderWindow(){ return &m_window; }
sf::View *Window::getView() { return &m_view; }
sf::Vector2u Window::getWindowSize(){ return m_windowSize; }
void Window::setColour(float colour[3]) { std::copy(colour, colour + 3, m_backgroundColour); }
float(&Window::getColour())[3] { return m_backgroundColour; }

void Window::resetView() { m_window.setView(m_view); }

void Window::toggleFullscreen(){
	m_isFullscreen = !m_isFullscreen;
	m_window.close();
	create();
}

void Window::update(){
	sf::Event event;
	while(m_window.pollEvent(event)){
		ImGui::SFML::ProcessEvent(event);
		if(event.type == sf::Event::Closed){ m_isDone = true; }
		else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape){ m_isDone = true; }
		else if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::F5){ toggleFullscreen(); }
		if (event.type == sf::Event::Resized) {
			// update the view to the new size of the window
			m_view.reset(sf::FloatRect(0, 0, event.size.width, event.size.height));
			resetView();
		}
	}
}

void Window::draw(sf::Drawable& l_drawable) {
	m_window.draw(l_drawable);
}