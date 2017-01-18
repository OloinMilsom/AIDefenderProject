#include "Astronaut.h"

Astronaut::Astronaut(float x, AlienManager * alienManager) : m_position(sf::Vector2f(x, 600)), m_alienManager(alienManager), m_beingAbducted(false), m_falling(false) {
	m_tex.loadFromFile("Resources/Astronaut.png");
	m_sprite = sf::Sprite(m_tex);// sf::IntRect(0, 0, m_tex.getSize().x, m_tex.getSize().y));
	m_sprite.setOrigin(m_tex.getSize().x / 2, m_tex.getSize().y / 2);

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
		if (!m_falling) {
			if (isAlienNear()) {
				avoid();
			}
			else {
				wander();
			}

			m_position.x += m_vel * dt;

			m_position.y = terrain->getHeightAt(m_position.x + m_tex.getSize().x / 2) - m_tex.getSize().y / 2;
		}
		else {
			m_position.y += 50 * dt;
			float h = terrain->getHeightAt(m_position.x + m_tex.getSize().x / 2) - m_tex.getSize().y / 2;
			if (h < m_position.y) {
				m_position.y = h;
				m_falling = false;
			}
		}
	}
	m_sprite.setTexture(m_tex);
	m_sprite.setPosition(m_position);
}

void Astronaut::render(sf::RenderWindow * window, Camera * camera) {
	if (m_alive) {
		window->draw((*camera) + m_sprite);
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

void Astronaut::setFalling(bool val) {
	m_falling = val;
}

