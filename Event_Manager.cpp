#include "Event_Manager.h"
#include <fstream>
#include <iostream>
#include <sstream>
Event_Manager::Event_Manager() : m_hasFocus(true) { LoadBindings(); }
Event_Manager::~Event_Manager()
{
	for (auto& itr : m_bindings)
	{
		delete itr.second;
		itr.second=nullptr ;
	}
}
bool Event_Manager::AddBinding(Binding* l_binding)
{
	if (m_bindings.find(l_binding->m_name) != m_bindings.end()) return false;
	return m_bindings.emplace(l_binding->m_name, l_binding).second;
}
bool Event_Manager::RemoveBinding(std::string& l_name)
{
	auto itr = m_bindings.find(l_name);
	if (itr == m_bindings.end()) return false;
	delete itr->second;
	m_bindings.erase(itr);
	return true;
}
void Event_Manager::SetFocus(const bool& l_focus) { m_hasFocus = l_focus; }
void Event_Manager::HandleEvent(sf::Event& l_event)
{
	for (auto& b_itr : m_bindings)
	{
		Binding* bind = b_itr.second;
		for (auto& e_itr : bind->m_events)
		{
			EventType sfmlEvent = (EventType)l_event.type;
			if (e_itr.first != sfmlEvent) continue;
			if (sfmlEvent == EventType::KeyDown || sfmlEvent == EventType::KeyUp)
			{
				if (e_itr.second.m_code == l_event.key.code)
				{
					if (bind->m_details.m_keyCode != -1) bind->m_details.m_keyCode = e_itr.second.m_code;

					++(bind->c);
					break;
				}
			} else if (sfmlEvent == EventType::MButtonDown || sfmlEvent == EventType::MButtonUp)
			{
				if (e_itr.second.m_code == l_event.mouseButton.button)
				{
					bind->m_details.m_mouse.x = l_event.mouseButton.x;
					bind->m_details.m_mouse.y = l_event.mouseButton.y;
					if (bind->m_details.m_keyCode != -1) bind->m_details.m_keyCode = e_itr.second.m_code;
					++(bind->c);
					break;
				}
			}
			else {
				if (sfmlEvent == EventType::MouseWheel) bind->m_details.m_mouseWheelDelta = l_event.mouseWheel.delta;
				else if (sfmlEvent == EventType::WindowResized) { bind->m_details.m_size.x = l_event.size.width; bind->m_details.m_size.y = l_event.size.height; }
				else if (sfmlEvent == EventType::TextEntered) bind->m_details.m_textEntered = l_event.text.unicode;
				++(bind->c);
			}
		} 
	}
}
void Event_Manager::Update()
{
	if (!m_hasFocus) return;
	for (auto& b_itr : m_bindings)
	{
		Binding* bind = b_itr.second;
		for (auto& e_itr : bind->m_events)
		{
			switch (e_itr.first)
			{
				case (EventType::Keyboard): if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key(e_itr.second.m_code)))
				{
					if (bind->m_details.m_keyCode != -1) bind->m_details.m_keyCode = e_itr.second.m_code;
					++(bind->c);
				}
				break;
			
				case (EventType::Mouse): if (sf::Mouse::isButtonPressed(sf::Mouse::Button(e_itr.second.m_code)))
				{
					if (bind->m_details.m_keyCode != -1) bind->m_details.m_keyCode = e_itr.second.m_code;
					++(bind->c);
				}
				break;


			

			}
		}
		if (bind->m_events.size() == bind->c) {
			auto callItr = m_callbacks.find(bind->m_name);
			if (callItr != m_callbacks.end()) {
				callItr->second(&bind->m_details);
			}
		}
		bind->c = 0;
		bind->m_details.Clear();
	}
}
void Event_Manager::LoadBindings()
{
	std::string delimeter = ":";
	std::ifstream bindings;
	bindings.open("keys.cfg");
	if (!bindings.is_open())
	{
		std::cout << "Failed to load cfg file!" << std::endl;
		return;
	}
	std::string line;
	while (std::getline(bindings, line))
	{
		std::stringstream keystream (line);
		std::string callbackName;
		keystream >> callbackName;
		Binding* bind = new Binding(callbackName);
		while (!keystream.eof())
		{
			std::string keyval;
			keystream >> keyval;
			if (keystream.fail()) {
				keystream.clear();
				break;
			}
			int start{ 0 };
			int end = keyval.find(delimeter);
			if (end == std::string::npos)
			{
				delete bind;
				bind = nullptr;
				break;
			}
			EventType type = EventType(std::stoi(keyval.substr(start, end - start)));
			int code = std::stoi(keyval.substr(end + delimeter.length(), keyval.find(delimeter, end + delimeter.length())));
			EventInfo eventInfo;
			eventInfo.m_code = code;
			bind->BindEvent(type, eventInfo);
		}
		if (!AddBinding(bind)) { delete bind;  }
		bind = nullptr;

	}
	bindings.close();

}
