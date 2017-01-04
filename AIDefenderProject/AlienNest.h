#pragma once

#include "Alien.h"

class AlienNest : public Alien {
private:

public:
	AlienNest(sf::Vector2f position, float speed, float acceleration);
	void update(float dt, AlienManager * data);
	void wander();
	void avoidBounds(const Terrain * terrain);
	void avoidPlayer(const Player * player, const Camera * camera);
};