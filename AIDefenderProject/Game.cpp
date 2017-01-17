#include "Game.h"

Game::Game () {
	srand(std::time(0));

	m_window = new sf::RenderWindow(sf::VideoMode(800, 600, 32), "SFML First Program");

	m_player = new Player();
	m_terrain = Terrain(m_window->getSize().x * 9, 500, 7);

	m_inputManager = InputManager(m_window);
	m_inputManager.addListener(sf::Event::Closed, this);
	m_inputManager.addListener(sf::Event::KeyPressed, this);
	m_inputManager.addListener(sf::Event::KeyPressed, m_player);
	m_inputManager.addListener(sf::Event::KeyReleased, m_player);

	m_camera = Camera(m_window->getSize().x, m_window->getSize().y, m_window->getSize().x * 9, m_window->getSize().y);

	m_alienManager = new AlienManager(m_player, &m_astronauts, &m_terrain, &m_camera);	
	
	for (int i = 0; i < 20; i++) {
		m_astronauts.push_back(Astronaut(rand() % (800 * 9), m_alienManager));
	}

	for (int i = 0; i < 20; i++) {
		m_alienManager->addNest(sf::Vector2f(rand() % (800 * 9), rand() % 600));
	}
}

void Game::update(float dt) {
	m_inputManager.processInput();
	m_player->update(dt);

	sf::Vector2f playerPos = m_player->getPosition();
	float temp = m_terrain.getMTV(playerPos);
	playerPos.y += temp;
	m_player->setPosition(playerPos);

	m_camera.update(playerPos);
	m_terrain.update();

	BulletManager::getInstance()->update();

	m_alienManager->update(dt);
	
	for (int i = 0; i < m_astronauts.size(); i++) {
		m_astronauts[i].update(dt, &m_terrain);
	}
}

void Game::render() {
	//prepare frame
	m_window->clear();

	m_player->render(m_window, &m_camera);
	m_terrain.render(m_window, &m_camera);
	BulletManager::getInstance()->render(m_window, &m_camera);

	for (int i = 0; i < m_astronauts.size(); i++) {
		m_astronauts[i].render(m_window, &m_camera);
	}

	m_alienManager->render(m_window, &m_camera);

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
				BulletManager::getInstance()->addBullet(m_player->getPosition(), sf::Vector2f(15.0f, 0), false, false); //Moving Right
			}
			else
			{
				BulletManager::getInstance()->addBullet(m_player->getPosition(), sf::Vector2f(-15.0f, 0), false, false); //Moving Left
			}
			
		default:
			break;
		}
		break;

	default:
		break;
	}
}
