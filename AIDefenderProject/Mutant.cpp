#include "Mutant.h"

Mutant::Mutant(sf::Vector2f position, float speed, float acceleration) : Alien(position, speed, acceleration) {
	m_type = AlienType::mutant;

	m_angle = acos(-1) * 2 * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	m_acceleration = sf::Vector2f(cos(m_angle), sin(m_angle)) * MAX_ACCELERATION;

	m_sprite.setSize(sf::Vector2f(20, 10));
	m_sprite.setFillColor(sf::Color::Cyan);
}

void Mutant::update(float dt, AlienManager * data) {
	wander();
	avoidBounds(data->getTerrain());
	move(dt);
}
