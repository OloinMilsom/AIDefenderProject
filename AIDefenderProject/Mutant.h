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

	enum AttackType {
		rotate,
		dive
	};

	const float PLAYER_FOLLOW = 100;
	const float PLAYER_REPULSE = 400;
	const float PLAYER_ATTACK_DISTANCE = 150;
	const float SWARM_DISTANCE = 400;
	const float SWARM_ATTRACTION = 1250;
	const float SWARM_ATTRACTION_EXP = 2;
	const float SWARM_REPULSION = 3750;
	const float SWARM_REPULSION_EXP = 3;

	static int m_rotateCount;
	static int m_diveCount;

	MutantState m_state;
	AttackType m_attackType;
	struct { float attackAngle; float attackDistance; int direction; } m_attackData;

	void swarm(AlienManager * data);
	void moveToPlayer(const Player * player, const Camera * camera, bool towards);
	void rotateAttack(float dt, AlienManager * data);
	void diveAttack(float dt, AlienManager * data);
public:
	Mutant(sf::Vector2f position, float speed, float acceleration); //!< Mutant constructor

	//! Mutant implementation of Alien update
	/*!
	see Alien::update
	Mutant behaviour described in class description.
	*/
	void update(float dt, AlienManager * data);
};