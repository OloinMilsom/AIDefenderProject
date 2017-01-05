#pragma once

#include "Alien.h"

class Abductor : public Alien {
private:

public:
	Abductor(sf::Vector2f position, float speed, float acceleration);
	void update(float dt, AlienManager * data);
};