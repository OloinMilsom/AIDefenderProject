#include "AlienNest.h"

AlienNest::AlienNest(sf::Vector2f position, float speed, float acceleration) : Alien(position, speed, acceleration) {
	m_type = AlienType::nest;

	m_angle = acos(-1) * 2 * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	m_velocity = sf::Vector2f(cos(m_angle), sin(m_angle)) * 0.0f;
	m_acceleration = sf::Vector2f(MAX_ACCELERATION, 0);

	m_sprite.setSize(sf::Vector2f(20, 10));
	m_sprite.setFillColor(sf::Color::Magenta);

	resetSpawnTimer();
}

void AlienNest::update(float dt, AlienManager * data) {
	wander();
	avoidBounds(data->getTerrain());
	avoidPlayer(data->getPlayer(), data->getCamera());

	m_spawnTimer -= dt;
	if (m_spawnTimer < 0) {
		data->addAbductor(m_position);
		resetSpawnTimer();
	}

	m_acceleration *= MAX_ACCELERATION / sqrt(m_acceleration.x * m_acceleration.x + m_acceleration.y * m_acceleration.y);

	m_velocity += m_acceleration * dt;

	float velLengthSquared = m_velocity.x * m_velocity.x + m_velocity.y * m_velocity.y;
	if (velLengthSquared > MAX_SPEED * MAX_SPEED) {
		m_velocity *= MAX_SPEED / sqrt(velLengthSquared);
	}

	m_velocity -= m_velocity * 0.1f * dt;

	m_position += m_velocity * dt;

	m_sprite.setPosition(m_position);
}

void AlienNest::wander() {
	if (rand() % 60 == 0) {
		float angle = 0.5f;
		if (rand() % 2 == 0) {
			angle = -angle;
		}
		m_acceleration = sf::Vector2f(cos(angle)*m_acceleration.x - sin(angle)*m_acceleration.y, sin(angle)*m_acceleration.x + cos(angle)*m_acceleration.y);
	}
}

void AlienNest::avoidBounds(const Terrain * terrain) {
	if (m_acceleration.y < 0) {
		m_acceleration.y += MAX_ACCELERATION * 100 / (m_position.y * m_position.y);
	}
	if (m_position.y < 0) {
		m_position.y = 0;
		m_velocity.y = 0;
	}

	float pointAtGround = terrain->getHeightAt(m_position.x);
	if (m_acceleration.y > 0) {
		m_acceleration.y -= MAX_ACCELERATION * 100 / ((pointAtGround - m_position.y) * (pointAtGround - m_position.y));
	}
	if (m_position.y > pointAtGround) {
		m_position.y = pointAtGround;
		m_velocity.y = 0;
	}
}

void AlienNest::avoidPlayer(const Player * player, const Camera * camera) {
	sf::Vector2f myAdjustedPos = (*camera) + m_position;
	sf::Vector2f playerAdjustedPos = (*camera) + player->getPosition();
	sf::Vector2f d = myAdjustedPos - playerAdjustedPos;
	float lengthSquared = d.x * d.x + d.y * d.y;
	d /= lengthSquared;
	m_acceleration += d * 750.0f;
}

void AlienNest::resetSpawnTimer() {
	m_spawnTimer = rand() % 3 + 3;
}
