#include "InputManager.h"

InputManager::InputManager(sf::Window * window) : m_window(window) {

}

InputManager::~InputManager() {

}

void InputManager::addListener(sf::Event::EventType evt, EventListener *listener) {
	if (m_listeners.find(evt) == m_listeners.end())
	{ //event not in map add it.
		m_listeners[evt] = new std::vector<EventListener*>();
	}

	m_listeners[evt]->push_back(listener);
}

void InputManager::addCallback(sf::Event::EventType evt, void(*func)(sf::Event)) {
	if (m_callbacks.find(evt) == m_callbacks.end())
	{ //event not in map add it.
		m_callbacks[evt] = new std::vector<void (*)(sf::Event)>();
	}

	m_callbacks[evt]->push_back(func);
}

//Send the events to interested objects
void InputManager::dispatch(sf::Event evt) {
	if (m_listeners.find(evt.type) != m_listeners.end())
	{
		for (auto const &listener : *m_listeners[evt.type]) { //go through all listeners for this event
			listener->onEvent(evt); //Call on event for the listener
		}
	}
	if (m_callbacks.find(evt.type) != m_callbacks.end())
	{
		for (auto const &callback : *m_callbacks[evt.type]) { //go through all listeners for this event
			callback(evt); //Call on event for the listener
		}
	}
}

void InputManager::processInput() {
	// Process events 
	sf::Event e;

	while (m_window->pollEvent(e))
	{
		switch (e.type) {
		case sf::Event::Closed:
			dispatch(e);
			break;
		case sf::Event::KeyPressed:
			dispatch(e);
			break;
		}


	}
}