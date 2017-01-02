#pragma once

#include "Alien.h"

class Mutant : public Alien {
private:

public:
	Mutant(sf::Vector2f position);
	void update(float dt, AlienManager * data);
};