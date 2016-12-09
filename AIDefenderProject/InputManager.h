#pragma once

#include "stdafx.h"
#include <map>
#include <vector>
#include "EventListener.h"

class InputManager {
private:
	std::map<sf::Event::EventType, std::vector<EventListener*>*> m_listeners;
	std::map<sf::Event::EventType, std::vector<void (*)(sf::Event)>*> m_callbacks;
	sf::Window * m_window;
public:
	InputManager(sf::Window * window = nullptr);
	~InputManager();

	void addListener(sf::Event::EventType, EventListener *);
	void addCallback(sf::Event::EventType, void(*func)(sf::Event));
	void dispatch(sf::Event);

	void processInput();
};