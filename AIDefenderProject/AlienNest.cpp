#include "AlienNest.h"

AlienNest::AlienNest(sf::Vector2f position, float speed, float acceleration) : Alien(position, speed, acceleration) {
	m_type = AlienType::nest;

	m_angle = acos(-1) * 2 * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	m_acceleration = sf::Vector2f(cos(m_angle), sin(m_angle)) * MAX_ACCELERATION;

	m_tex.loadFromFile("Resources/Nest.png");
	m_sprite = sf::Sprite(m_tex, sf::IntRect(0, 0, m_tex.getSize().x / 6, m_tex.getSize().y));
	m_sprite.setOrigin(m_tex.getSize().x / 12, m_tex.getSize().y / 2);

	m_health = 1;
	m_missileA = true;
	m_missileB = true;

	srand(time(NULL));

	resetSpawnTimer();
}

void AlienNest::update(float dt, AlienManager * data) {
	if (m_alive)
	{
		wander();
		avoidBounds(data->getTerrain());
		avoidPlayer(data->getPlayer(), data->getCamera());

		m_spawnTimer -= dt;
		if (m_spawnTimer < 0) {
			data->addAbductor(m_position);
			resetSpawnTimer();
		}

		if (rand() % 1000 == 1)
		{
			if (m_missileA)
			{
				fireMissile(data->getPlayer());
				m_missileA = false;
				m_missileATime = m_clock.getElapsedTime();
			}
			else if (m_missileB)
			{
				fireMissile(data->getPlayer());
				m_missileB = false;
				m_missileBTime = m_clock.getElapsedTime();
			}
			
		}

		if (m_clock.getElapsedTime() - m_missileATime > m_missileCooldown && !m_missileA)
		{
			m_missileA = true;
		}
		if (m_clock.getElapsedTime() - m_missileBTime > m_missileCooldown && !m_missileB)
		{
			m_missileB = true;
		}

		m_sprite.setTextureRect(sf::IntRect(abs(static_cast<int>(m_position.x / 30) % 6) * (m_tex.getSize().x / 6), 0, m_tex.getSize().x / 6, m_tex.getSize().y));
		move(dt);
	}

}

void AlienNest::fireMissile(const Player * player)
{
	BulletManager::getInstance()->addTrackingBullet(m_position, sf::Vector2f(3.0f, 1.0f));
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
