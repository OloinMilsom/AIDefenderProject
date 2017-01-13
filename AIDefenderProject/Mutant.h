#pragma once

#include "Alien.h"

class Mutant : public Alien {
private:
	const float PLAYER_FOLLOW = 1000;
	const float PLAYER_REPULSE = 4000;
	const float SWARM_DISTANCE = 400;
	const float SWARM_ATTRACTION = 1750;
	const float SWARM_ATTRACTION_EXP = 2;
	const float SWARM_REPULSION = 250;
	const float SWARM_REPULSION_EXP = 3;

	void swarm(AlienManager * data);
	void moveToPlayer(const Player * player, const Camera * camera);
public:
	Mutant(sf::Vector2f position, float speed, float acceleration);
	void update(float dt, AlienManager * data);
};