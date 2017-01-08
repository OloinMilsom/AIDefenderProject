#pragma once

#include "Alien.h"

class Abductor : public Alien {
private:
	const float FLOCK_DISTANCE = 100;
	const float ALIGNMENT = 100;
	const float COHESION = 1000;
	const float SEPARATION = 150;

	void flock(AlienManager * data);
	void combineAcceleration(sf::Vector2f other);
public:
	Abductor(sf::Vector2f position, float speed, float acceleration);
	void update(float dt, AlienManager * data);
};