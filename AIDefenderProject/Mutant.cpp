#include "Mutant.h"

Mutant::Mutant(sf::Vector2f position, float speed, float acceleration) : Alien(position, speed, acceleration) {
	m_type = AlienType::mutant;
	m_state = MutantState::following;

	m_angle = acos(-1) * 2 * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	m_acceleration = sf::Vector2f(cos(m_angle), sin(m_angle)) * MAX_ACCELERATION;

	m_sprite.setSize(sf::Vector2f(20, 10));
	m_sprite.setFillColor(sf::Color::Cyan);
}

void Mutant::update(float dt, AlienManager * data) {
	switch (m_state) {
	case MutantState::following:
		wander();
		avoidBounds(data->getTerrain());
		moveToPlayer(data->getPlayer(), data->getCamera(), true);
		swarm(data);
		move(dt);
		break;
	default:
		break;
	}
}

void Mutant::swarm(AlienManager * data) {
	/*Pvector	R;
	int A = 100;
	int B = 5000;
	int N = 1;
	int M = 2;
	int count = 0;
	float totalForce = 0;
	Pvector sum(0, 0);

	for (int i = 0; i < v.size(); i++)
	{
		R = R.subTwoVector(location, v[i].location);
		float D = R.magnitude();
		if (D > 0)
		{
			float U = -A / pow(D, N) + B / pow(D, M);
			R.normalize();
			R.mulScalar(U);
			sum.addVector(R);
		}

	}
	sum.divScalar(v.size() - 1);
	applyForce(sum);
	update();
	borders();*/
	for (auto iter = data->mutantBegin(); iter != data->mutantEnd(); iter++) {
		if ((*iter)->getPos() != m_position) {
			sf::Vector2f d = ((*data->getCamera()) + (*iter)->getPos()) - ((*data->getCamera()) + m_position);
			float distSqr = d.x * d.x + d.y * d.y;
			float dist = sqrt(distSqr);
			if (dist < SWARM_DISTANCE) {
				m_acceleration += d * ((SWARM_ATTRACTION / std::pow(dist, SWARM_ATTRACTION_EXP)) - (SWARM_REPULSION / std::pow(dist, SWARM_REPULSION_EXP)));
			}
		}
	}
}

void Mutant::moveToPlayer(const Player * player, const Camera * camera, bool towards) {
	sf::Vector2f myAdjustedPos = (*camera) + m_position;
	sf::Vector2f playerAdjustedPos = (*camera) + player->getPosition();
	sf::Vector2f d =  playerAdjustedPos - myAdjustedPos;
	float lengthSquared = d.x * d.x + d.y * d.y;
	float length = sqrt(lengthSquared);
	
	if (towards) {
		m_acceleration += d * ((PLAYER_FOLLOW / length) - (PLAYER_REPULSE / (lengthSquared)));
	}
	else {
		m_acceleration -= d * ((PLAYER_FOLLOW / length) - (PLAYER_REPULSE / (lengthSquared)));
	}
}
