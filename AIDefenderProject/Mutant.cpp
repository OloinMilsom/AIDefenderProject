#include "Mutant.h"

Mutant::Mutant(sf::Vector2f position, float speed, float acceleration) : Alien(position, speed, acceleration) {
	m_health = 2;
}

void Mutant::update(float dt, AlienManager * data) {
}
