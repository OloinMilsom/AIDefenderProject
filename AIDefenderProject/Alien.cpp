#include "Alien.h"

Alien::Alien(sf::Vector2f pos, float speed, float acceleration) : m_position(pos), MAX_SPEED(speed), MAX_ACCELERATION(acceleration), m_alive(true) {
}

void Alien::render(sf::RenderWindow * window, Camera * camera) {
	sf::RectangleShape temp = m_sprite;
	temp.setPosition((*camera) + temp.getPosition());

	sf::VertexArray velAccel(sf::Lines, 4);
	velAccel[0].position = (*camera) + m_position;
	velAccel[0].color = sf::Color::Blue;
	velAccel[1].position = (*camera) + m_position + m_velocity;
	velAccel[1].color = sf::Color::Blue;	
	velAccel[2].position = (*camera) + m_position;
	velAccel[2].color = sf::Color::Green;
	velAccel[3].position = (*camera) + m_position + m_acceleration;
	velAccel[3].color = sf::Color::Green;
	window->draw(temp);
	window->draw(velAccel);
}

void Alien::move(float dt) {

	if (m_acceleration.x != 0 || m_acceleration.y != 0) {
		m_acceleration *= MAX_ACCELERATION / sqrt(m_acceleration.x * m_acceleration.x + m_acceleration.y * m_acceleration.y);

		m_velocity += m_acceleration * dt;
	}

	float velLengthSquared = m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y;
	if (velLengthSquared > MAX_SPEED * MAX_SPEED) {
		m_velocity *= MAX_SPEED / sqrt(velLengthSquared);
	}

	m_velocity -= m_velocity * 0.1f * dt;

	m_position += m_velocity * dt;

	m_sprite.setPosition(m_position);
}

void Alien::wander() {
	if (rand() % 60 == 0) {
		float angle = 0.5f;
		if (rand() % 2 == 0) {
			angle = -angle;
		}
		m_acceleration = sf::Vector2f(cos(angle)*m_acceleration.x - sin(angle)*m_acceleration.y, sin(angle)*m_acceleration.x + cos(angle)*m_acceleration.y);
	}
}

void Alien::avoidBounds(const Terrain * terrain) {
	if (m_velocity.y < 0) {
		m_acceleration.y += MAX_ACCELERATION * 500 / (m_position.y * m_position.y);
	}
	if (m_position.y < 0) {
		m_position.y = 0;
		m_velocity.y = 0;
	}

	float pointAtGround = terrain->getHeightAt(m_position.x);
	if (m_velocity.y > 0) {
		m_acceleration.y -= MAX_ACCELERATION * 500 / ((pointAtGround - m_position.y) * (pointAtGround - m_position.y));
	}
	if (m_position.y > pointAtGround) {
		m_position.y = pointAtGround;
		m_velocity.y = 0;
	}
}

AlienType Alien::getType() {
	return m_type;
}

sf::Vector2f Alien::getPos() { 
	return m_position;
}

sf::Vector2f Alien::getVel() {
	return m_velocity;
}

sf::Vector2f Alien::getAccel() {
	return m_acceleration;
}
