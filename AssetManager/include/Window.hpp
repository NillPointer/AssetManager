#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <string>
#include "core.hpp"

class Window{
public:
	Window();
	Window(const std::string& title, const sf::Vector2u& size);
	~Window();

	void beginDraw();
	void endDraw();

	void update();

	bool isDone();
	bool isFullscreen();
	sf::RenderWindow *getRenderWindow();
	sf::View *getView();
	sf::Vector2u getWindowSize();
	void setColour(float colour[3]);
	float (&getColour())[3];

	void resetView();
	void toggleFullscreen();

	void draw(sf::Drawable& l_drawable);
private:
	void setup(const std::string title, const sf::Vector2u& size);
	void create();
	void destroy();

	sf::RenderWindow m_window;
	sf::View m_view;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullscreen;
	float m_backgroundColour[3] = { 125, 125, 125 };
};

#endif /* WINDOW_HPP */
