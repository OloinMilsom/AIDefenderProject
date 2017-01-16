#pragma once

#include "Alien.h"

//! AlienNest type alien
/*!
AlienNest type aliens avoid the player, firing guided missiles if they stray too
close. Other than that these aliens simply wander and spawn abductors at random
intervals.
*/
class AlienNest : public Alien {
private:
	float m_spawnTimer;

	void avoidPlayer(const Player * player, const Camera * camera);
	void resetSpawnTimer();
public:
	AlienNest(sf::Vector2f position, float speed, float acceleration); //!< AlienNest constructor
	
	//! AlienNest implementation of Alien update
	/*!
	see Alien::update
	AlienNest behaviour described in class description.
	*/
	void update(float dt, AlienManager * data);
};