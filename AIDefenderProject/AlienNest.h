#pragma once

#include "Alien.h"

class AlienNest : public Alien {
private:
	const int MAX_MISSILE = 2;
	int m_missileCount;
	float m_spawnTimer;

	void avoidPlayer(const Player * player, const Camera * camera);
	void resetSpawnTimer();
public:
	AlienNest(sf::Vector2f position, float speed, float acceleration);
	void update(float dt, AlienManager * data);
	void fireMissile(const Player * player);
};