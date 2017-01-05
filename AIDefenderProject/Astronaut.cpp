#include "Astronaut.h"

Astronaut::Astronaut(float x, AlienManager * alienManager) : m_position(sf::Vector2f(x, 0)) {
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

	m_alienManager = alienManager;
}

void Astronaut::update(float dt, Terrain * terrain) {
	if (isAlienNear())
	{
		avoid();
	}
	else
	{
		wander();
	}


	m_position.x += m_vel * dt;

	m_position.y = terrain->getHeightAt(m_position.x + m_sprite.getSize().x / 2) - m_sprite.getSize().y;

	m_sprite.setPosition(m_position);
}

void Astronaut::render(sf::RenderWindow * window, Camera * camera) {
	sf::RectangleShape temp = m_sprite;
	temp.setPosition((*camera) + temp.getPosition());
	window->draw(temp);
}

void Astronaut::avoid()
{
	if (m_alienManager->getAll()->at(avoidTarget)->getPos().x > m_position.x) {
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
		m_vel = 0;
	}

}

bool Astronaut::isAlienNear()
{
	for (int i = 0; i < m_alienManager->getAll()->size; i++)
	{
		sf::Vector2f length = m_alienManager->getAll()->at(i)->getPos() - m_position;
		length.x *= length.x;
		length.y *= length.y;
		if (length.x + length.y > 50)
		{
			avoidTarget = i;
			return true;
		}
	}
	return false;
}


