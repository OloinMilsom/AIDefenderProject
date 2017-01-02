#include "AlienNest.h"

AlienNest::AlienNest(sf::Vector2f position, float speed) : Alien(position, speed) {
	m_angle = acos(-1) * 2 * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	m_velocity = sf::Vector2f(cos(m_angle), sin(m_angle));

	m_sprite.setSize(sf::Vector2f(20, 10));
}

void AlienNest::update(float dt, AlienManager * data) {
	m_angle += 0.1f;
	if (m_angle > 2 * acos(-1)) {
		m_angle -= 2 * acos(-1);
	}
	if (m_angle < 0) {
		m_angle -= 2 * acos(-1);
	}
	m_velocity = sf::Vector2f(cos(m_angle), sin(m_angle));
	m_position += m_velocity * SPEED * dt;
	m_sprite.setPosition(m_position);
}
