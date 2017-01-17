#pragma once

#include "Alien.h"

//! Mutant type alien
/*!
Mutant type aliens collect into swarms. They aggresively seek the player and will
attack the player using some intelligent behaviours.
*/

class Mutant : public Alien {
private:
	enum MutantState {
		following,
		attacking,
		fleeing
	};

	const float PLAYER_FOLLOW = 100;
	const float PLAYER_REPULSE = 400;
	const float SWARM_DISTANCE = 4000;
	const float SWARM_ATTRACTION = 1750;
	const float SWARM_ATTRACTION_EXP = 2;
	const float SWARM_REPULSION = 3250;
	const float SWARM_REPULSION_EXP = 3;

	MutantState m_state;

	void swarm(AlienManager * data);
	void moveToPlayer(const Player * player, const Camera * camera, bool towards);
public:
	Mutant(sf::Vector2f position, float speed, float acceleration); //!< Mutant constructor

	//! Mutant implementation of Alien update
	/*!
	see Alien::update
	Mutant behaviour described in class description.
	*/
	void update(float dt, AlienManager * data);
};