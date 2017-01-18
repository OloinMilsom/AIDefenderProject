#pragma once

#include "stdafx.h"
#include <map>
#include <vector>
#include "EventListener.h"

//! InputManager class
/*!
Checks for keyboard input and dispatches events to any subscribed EventListener
*/
class InputManager {
private:
	std::map<sf::Event::EventType, std::vector<EventListener*>*> m_listeners;
	std::map<sf::Event::EventType, std::vector<void (*)(sf::Event)>*> m_callbacks;
	sf::Window * m_window;
public:
	InputManager(sf::Window * window = nullptr); //!< InputManager constructor
	~InputManager(); //<! InputManager destructor

	void addListener(sf::Event::EventType, EventListener *); //!< adds an EventListener and subscribes it to an EventType
	void addCallback(sf::Event::EventType, void(*func)(sf::Event)); //!< adds an function pointer and subscribes it to an EventType
	void dispatch(sf::Event); //!< calls onEvent for all EventListeners subscribed to the Event

	void processInput(); //!< checks to see if any keyboard events have fired
};