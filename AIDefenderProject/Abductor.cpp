#include "Abductor.h"


Abductor::Abductor(sf::Vector2f position, float speed, float acceleration) : Alien(position, speed, acceleration) {
	m_type = AlienType::abductor;
	m_sprite.setSize(sf::Vector2f(20, 10));
	m_sprite.setFillColor(sf::Color::Yellow);
}

void Abductor::update(float dt, AlienManager * data) {
	m_sprite.setPosition(m_position);
}
