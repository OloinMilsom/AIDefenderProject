#pragma once

#include "Alien.h"

class Abductor : public Alien {
private:

public:
	Abductor(sf::Vector2f position);
	void update(float dt, AlienManager * data);
};