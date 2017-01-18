#include "Mutant.h"

int Mutant::m_rotateCount = 0;
int Mutant::m_diveCount = 0;

Mutant::Mutant(sf::Vector2f position, float speed, float acceleration) : Alien(position, speed, acceleration) {
	m_type = AlienType::mutant;
	m_health = 2;
	m_state = MutantState::following;

	m_angle = acos(-1) * 2 * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	m_acceleration = sf::Vector2f(cos(m_angle), sin(m_angle)) * MAX_ACCELERATION;

	m_tex.loadFromFile("Resources/Mutant.png");
	m_sprite = sf::Sprite(m_tex, sf::IntRect(0, 0, m_tex.getSize().x, m_tex.getSize().y));
	m_sprite.setOrigin(m_tex.getSize().x / 2, m_tex.getSize().y / 2);
}

void Mutant::update(float dt, AlienManager * data) {
	if (m_alive)
	{
		sf::Vector2f d = ((*data->getCamera()) + data->getPlayer()->getPosition()) - ((*data->getCamera()) + m_position);
		switch (m_state) {
		case MutantState::following:
			wander();
			avoidBounds(data->getTerrain());
			moveToPlayer(data->getPlayer(), data->getCamera(), true);
			swarm(data);
			move(dt);
			if (d.x * d.x + d.y * d.y < PLAYER_ATTACK_DISTANCE * PLAYER_ATTACK_DISTANCE) {
				m_state = MutantState::attacking;
				m_attackData.attackAngle = atan(d.y / d.x);
				if (d.x > 0) {
					m_attackData.attackAngle += acos(-1);
				}
				m_attackData.direction = 1;
				if (rand() % 2 == 0) {
					m_attackData.direction = -1;
				}
				m_attackData.attackDistance = sqrt(d.x * d.x + d.y * d.y) - PLAYER_ATTACK_DISTANCE;

				if (m_rotateCount < 3) {
					m_attackType = AttackType::rotate;
					m_rotateCount++;
				}
				else {
					m_attackType = AttackType::dive;
					m_diveCount++;
				}
			}
			break;

		case MutantState::attacking:
			switch (m_attackType) {
			case AttackType::rotate:
				rotateAttack(dt, data);
				if (m_rotateCount > 3) {
					m_rotateCount--;
					m_attackType = AttackType::dive;
					m_diveCount++;
				}
				break;

			case AttackType::dive:
				diveAttack(dt, data);
				if (m_rotateCount < 3) {
					m_diveCount--;
					m_attackType = AttackType::rotate;
					m_rotateCount++;
				}
				break;
			}
			if (m_health <= 1) {
				m_state = MutantState::fleeing;
			}
			m_sprite.setPosition(m_position);
			break;

		case MutantState::fleeing:
			wander();
			avoidBounds(data->getTerrain());
			moveToPlayer(data->getPlayer(), data->getCamera(), false);
			swarm(data);
			move(dt);
			break;

		default:
			break;
		}
	}
	
}

void Mutant::swarm(AlienManager * data) {
	int swarmCount = 0;
	for (auto iter = data->mutantBegin(); iter != data->mutantEnd(); iter++) {
		if ((*iter)->getPos() != m_position && static_cast<Mutant *>(*iter)->m_state == MutantState::following) {
			sf::Vector2f d = ((*data->getCamera()) + (*iter)->getPos()) - ((*data->getCamera()) + m_position);
			float distSqr = d.x * d.x + d.y * d.y;
			float dist = sqrt(distSqr);
			if (dist < SWARM_DISTANCE) {
				swarmCount++;
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

void Mutant::rotateAttack(float dt, AlienManager * data) {
	m_attackData.attackAngle += 0.9 * dt * m_attackData.direction;
	m_position = data->getPlayer()->getPosition() + (PLAYER_ATTACK_DISTANCE + m_attackData.attackDistance) * sf::Vector2f(cos(m_attackData.attackAngle), sin(m_attackData.attackAngle));

	float terrainPos = data->getTerrain()->getHeightAt(m_position.x);
	if (terrainPos <= m_position.y) {
		m_position.y = terrainPos;
	}
	if (m_position.y < 0) {
		m_position.y = 0;
	}
}

void Mutant::diveAttack(float dt, AlienManager * data) {
	if (m_attackData.attackDistance < -(PLAYER_ATTACK_DISTANCE / 2)) {
		m_attackData.direction = 1;
	}
	if (m_attackData.attackDistance > (PLAYER_ATTACK_DISTANCE / 2)) {
		m_attackData.direction = -1;
	}
	m_attackData.attackDistance += m_attackData.direction * 120 * dt;
	m_position = data->getPlayer()->getPosition() + (PLAYER_ATTACK_DISTANCE + m_attackData.attackDistance) * sf::Vector2f(cos(m_attackData.attackAngle), sin(m_attackData.attackAngle));

	float terrainPos = data->getTerrain()->getHeightAt(m_position.x);
	if (terrainPos <= m_position.y) {
		m_position.y = terrainPos;
	}
	if (m_position.y < 0) {
		m_position.y = 0;
	}
}
