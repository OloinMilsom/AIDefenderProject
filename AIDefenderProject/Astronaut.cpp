#include "Astronaut.h"

Astronaut::Astronaut(float x, AlienManager * alienManager) : m_position(sf::Vector2f(x, 0)), m_alienManager(alienManager), m_beingAbducted(false) {
	m_sprite = sf::RectangleShape(sf::Vector2f(10, 10)); 
	int rnd = rand() % 3;
	if (rnd == 0) {
		m_vel = 0;
	}
	else if (rnd == 1) {
		m_vel = X_SPEED;
	}
	else if (rnd == 2) {
		m_vel = -X_SPEED;
	}
}

void Astronaut::update(float dt, Terrain * terrain) {
	if (!m_beingAbducted && m_alive) {
		if (isAlienNear()) {
			avoid();
		}
		else {
			wander();
		}


		m_position.x += m_vel * dt;

		m_position.y = terrain->getHeightAt(m_position.x + m_sprite.getSize().x / 2) - m_sprite.getSize().y;
	}
	m_sprite.setPosition(m_position);
}

void Astronaut::render(sf::RenderWindow * window, Camera * camera) {
	if (m_alive) {
		sf::RectangleShape temp = m_sprite;
		temp.setPosition((*camera) + temp.getPosition());
		window->draw(temp);
	}
}

void Astronaut::avoid()
{
	if (m_alienManager->getAll()[avoidTarget]->getPos().x > m_position.x) {
		m_vel = -X_SPEED;
	}
	else {
		m_vel = X_SPEED;
	}
}

void Astronaut::wander()
{
	int rnd = rand() % 1200;
	if (rnd == 0) {
		m_vel = -m_vel;
	}

}

bool Astronaut::isAlienNear()
{
	auto aliens = m_alienManager->getAll();
	float lowest = std::numeric_limits<float>::max();

	for (int i = 0; i < aliens.size(); i++)
	{
		sf::Vector2f alienPos = aliens[i]->getPos() - m_position;
		alienPos.x *= alienPos.x;
		alienPos.y *= alienPos.y;

		float length = sqrt(alienPos.x) + sqrt(alienPos.y);

		if (length < 400)
		{
			if (length < lowest)
			{
				lowest = length;
				avoidTarget = i;
			}
		}
	}

	return lowest != std::numeric_limits<float>::max();
}

sf::Vector2f Astronaut::getPos() const {
	return m_position;
}

bool Astronaut::getAlive() const {
	return m_alive;
}

void Astronaut::setPos(sf::Vector2f val) {
	m_position = val;
}

void Astronaut::setBeingAbducted(bool val) {
	m_beingAbducted = val;
}

void Astronaut::setAlive(bool val) {
	m_alive = val;
}


