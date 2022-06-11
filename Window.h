#ifndef  WINDOW_H
#define WINDOW_H
#include "Event_Manager.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <iostream>
#include <vector>
#include <sstream>
class Window
{
public:
	Window();
	Window(const std::string& l_title, const sf::Vector2u& l_size);
	~Window();
	void BeginDraw();
	void EndDraw();
	void Update();
	bool IsDone();
	bool IsFullScreen();
	sf::Vector2u GetWindowSize();
	void ToggleFullScreen();
	void Draw(sf::Drawable& l_drawable);
	bool IsFocused();
	Event_Manager* GetEventManager();
	void ToggleFullScreen(EventDetails* l_details);
	void Close(EventDetails* l_details =nullptr);
	sf::RenderWindow* GetRenderWindow() { return &m_window; }

private:
	void Setup(const std::string& l_title, const sf::Vector2u& l_size);
	void Destroy();
	void Create();
	sf::RenderWindow m_window;
	sf::Vector2u m_windowSize;
	std::string m_windowTitle;
	bool m_isDone;
	bool m_isFullScreen;
	Event_Manager m_eventManager;
	bool m_isFocused;
};
#endif

