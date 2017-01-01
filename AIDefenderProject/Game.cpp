#include "Game.h"

Game::Game () {
	srand(std::time(0));

	m_window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "SFML First Program");

	m_player = new Player();
	m_terrain = Terrain(m_window->getSize().x, 500, 7);

	m_inputManager = InputManager(m_window);
	m_inputManager.addListener(sf::Event::Closed, this);
	m_inputManager.addListener(sf::Event::KeyPressed, this);
	m_inputManager.addListener(sf::Event::KeyPressed, m_player);
	m_inputManager.addListener(sf::Event::KeyReleased, m_player);

	m_bulletManager = BulletManager();

	m_camera = Camera(m_window->getSize().x, m_window->getSize().y);
}

void Game::update(float dt) {
	m_inputManager.processInput();
	m_player->update(dt);

	sf::Vector2f playerPos = m_player->getPosition();
	float temp = m_terrain.underneath(playerPos);
	playerPos.y += temp;
	m_player->setPosition(playerPos);

	m_camera.update(playerPos);
	m_terrain.update();

	m_bulletManager.update();
}

void Game::render() {
	//prepare frame
	m_window->clear();

	m_player->render(m_window, m_camera);
	m_terrain.render(m_window, m_camera);
	m_bulletManager.render(m_window, m_camera);

	// Finally, display rendered frame on screen 
	m_window->display();
}

void Game::loop() {
	while (m_window->isOpen()) {
		float now = m_clock.getElapsedTime().asSeconds();
		float dt = now - m_lastFrameTime;

		update(dt);
		render();

		m_lastFrameTime = now;
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
		case sf::Keyboard::Space:
			if (m_player->getDirection())
			{
				m_bulletManager.addBullet(m_player->getPosition(), sf::Vector2f(0.1f, 0), false); //Moving Right
			}
			else
			{
				m_bulletManager.addBullet(m_player->getPosition(), sf::Vector2f(-0.1f, 0), false); //Moving Left
			}
			
		default:
			break;
		}
		break;

	default:
		break;
	}
}
