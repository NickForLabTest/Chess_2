#include "Window.h"

Window::Window() { Setup("Window", sf::Vector2u(800, 600)); }
Window::Window(const std::string& l_title, const sf::Vector2u& l_size)
{
	Setup(l_title, l_size);
}
Window::~Window() { Destroy(); }

void Window::Setup(const std::string& l_title, const sf::Vector2u& l_size)
{
	m_windowTitle = l_title;
	m_windowSize = l_size;
	m_isFullScreen = false;
	m_isDone = false;
	m_isFocused = true;
	m_eventManager.AddCallBack("Fullscreen_toggle", &Window::ToggleFullScreen, this);
	m_eventManager.AddCallBack("Window_close", &Window::Close, this);
	Create();
}
void Window::Create()
{
	/*auto style{ m_isFullScreen ? sf::Style::Fullscreen : sf::Style::Default };
	m_window.create({ m_windowSize.x,m_windowSize.y,32 }, m_windowTitle, style);*/
	sf::Uint32 style = sf::Style::Default;
	if (m_isFullScreen) { style = sf::Style::Fullscreen; }

	m_window.create(sf::VideoMode(m_windowSize.x, m_windowSize.y, 32), m_windowTitle, style);

}
void Window::Destroy() { m_window.close(); }
void Window::Update()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::LostFocus) {
			m_isFocused = false;
			m_eventManager.SetFocus(false);
		}
		else if (event.type == sf::Event::GainedFocus)
		{
			m_isFocused = true;
			m_eventManager.SetFocus(true);
		}
		m_eventManager.HandleEvent(event);
	}
	m_eventManager.Update();
}
void Window::ToggleFullScreen()
{
	m_isFullScreen = !m_isFullScreen;
	Destroy();
	Create();
}
void Window::ToggleFullScreen(EventDetails* l_details)
{
	m_isFullScreen = !m_isFullScreen;
	Destroy();
	Create();
}
void Window::BeginDraw() { m_window.clear(sf::Color::Black); }
void Window::EndDraw() { m_window.display(); }
bool Window::IsDone(){ return m_isDone; }
bool Window::IsFullScreen() { return m_isFullScreen; }
sf::Vector2u Window::GetWindowSize() { return m_windowSize; }
void Window::Draw(sf::Drawable& l_drawable) { m_window.draw(l_drawable); }
void Window::Close(EventDetails* l_details) { m_isDone = true; }
bool Window::IsFocused() { return m_isFocused; }
Event_Manager* Window::GetEventManager() { return &m_eventManager; }







