#pragma once

#include "Alien.h"

//! Abductor type alien
/*!
Abductor type aliens move around in flocks in order to find astronauts. When they
find an astronaut they will catch and abduct it, moving slowly towards the top of
the screen. If they succeed in abducting an astronaut, the astronaut will become
a mutant. Abductors fire single bullets at the player if close enough.
*/
class Abductor : public Alien {
private:
	const float FLOCK_DISTANCE = 100;
	const float ALIGNMENT = 100;
	const float COHESION = 1000;
	const float SEPARATION = 450;
	const float CHASE_DISTANCE = 150;
	const float ABDUCT_DISTANCE = 20;
	const float ABDUCT_SPEED = 50;

	static std::vector<int> m_chasedIndices;

	int m_chaseIndex;
	bool m_inFlock;
	bool m_chasing;
	bool m_abducting;

	void flock(AlienManager * data);
	void combineAcceleration(sf::Vector2f other);
	void chaseAstronaut(AlienManager * data);
public:
	Abductor(sf::Vector2f position, float speed, float acceleration); //!< Abductor constructor
	
	//! Abductor implementation of Alien update
	/*!
		see Alien::update
		Abductor behaviour described in class description.
	*/
	void update(float dt, AlienManager * data);
};