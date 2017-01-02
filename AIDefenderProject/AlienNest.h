#pragma once

#include "Alien.h"

class AlienNest : public Alien {
private:

public:
	AlienNest(sf::Vector2f position, float speed);
	void update(float dt, AlienManager * data);
};