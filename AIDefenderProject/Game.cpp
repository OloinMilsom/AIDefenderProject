#include "Game.h"

void Game::update() {
	m_inputManager.processInput();
}

void Game::render() {
	//prepare frame
	m_window->clear();
	// Finally, display rendered frame on screen 
	m_window->display();
}

Game::Game (){
	m_window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "SFML First Program");
	m_inputManager = InputManager(m_window);
	m_inputManager.addListener(sf::Event::Closed, this);
	m_inputManager.addListener(sf::Event::KeyPressed, this);
}

void Game::loop() {
	while (m_window->isOpen()) {
		update();
		render();
	}
}

void Game::onEvent(sf::Event evt) {
	switch (evt.type){
	case sf::Event::Closed:
		m_window->close();
		break;

	case sf::Event::KeyPressed:
		switch (evt.key.code) {
		case sf::Keyboard::Escape:
			m_window->close();
			break;
		default:
			break;
		}
		break;

	default:
		break;
	}
}
