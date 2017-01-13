#include "AlienNest.h"

AlienNest::AlienNest(sf::Vector2f position, float speed, float acceleration) : Alien(position, speed, acceleration) {
	m_type = AlienType::nest;

	m_angle = acos(-1) * 2 * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	m_acceleration = sf::Vector2f(cos(m_angle), sin(m_angle)) * MAX_ACCELERATION;

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
		data->addMutant(m_position);
		resetSpawnTimer();
	}

	move(dt);
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
	m_spawnTimer = rand() % 7 + 3;
}
