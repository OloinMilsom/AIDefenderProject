#include "Abductor.h"

std::vector<int> Abductor::m_chasedIndices;

Abductor::Abductor(sf::Vector2f position, float speed, float acceleration) : Alien(position, speed, acceleration), m_inFlock(false), m_chasing(false) {
	m_type = AlienType::abductor;

	m_angle = acos(-1) * 2 * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	m_acceleration = sf::Vector2f(cos(m_angle), sin(m_angle)) * MAX_ACCELERATION;

	m_sprite.setSize(sf::Vector2f(20, 10));
	m_sprite.setFillColor(sf::Color::Yellow);
}

void Abductor::update(float dt, AlienManager * data) {
	wander();
	avoidBounds(data->getTerrain());
	flock(data);

	move(dt);
}

void Abductor::flock(AlienManager * data) {
	// first find neighbours
	std::vector<Abductor *> neighbours;
	sf::Vector2f averageAccel;
	sf::Vector2f averagePos;

	for (auto iter = data->abductorBegin(); iter != data->abductorEnd(); iter++) {
		sf::Vector2f curPos = (*data->getCamera()) + (*iter)->getPos();
		sf::Vector2f distance = curPos - ((*data->getCamera()) + m_position);
		if (distance.x * distance.x + distance.y * distance.y < FLOCK_DISTANCE * FLOCK_DISTANCE) {
			averageAccel += (*iter)->getAccel();
			averagePos += (*data->getCamera()) + (*iter)->getPos();
			neighbours.push_back(static_cast<Abductor *>(*iter));
		}
	}

	averageAccel /= static_cast<float>(neighbours.size());
	averagePos /= static_cast<float>(neighbours.size());

	// alignment, cohesion and seperation
	if (neighbours.size() > 1) {
		m_inFlock = true;
		for (int i = 0; i < neighbours.size(); i++) {
			neighbours[i]->combineAcceleration(averageAccel * ALIGNMENT);

			sf::Vector2f toCentre = averagePos - neighbours[i]->getPos();
			float distanceSquared = toCentre.x * toCentre.x + toCentre.y * toCentre.y;
			toCentre /= sqrt(distanceSquared);

			neighbours[i]->combineAcceleration(toCentre * (COHESION / distanceSquared));
			
			for (int j = 0; j < neighbours.size(); j++) {
				if (i != j) {
					sf::Vector2f toOther = neighbours[i]->getPos() - neighbours[j]->getPos();
					float distanceToOtherSquared = toOther.x * toOther.x + toOther.y * toOther.y;
					toCentre /= sqrt(distanceToOtherSquared);
					neighbours[i]->combineAcceleration(toOther * (SEPARATION / distanceToOtherSquared));
				}
			}
		}
	}
	else {
		m_inFlock = false;
	}
}

void Abductor::combineAcceleration(sf::Vector2f other) {
	m_acceleration += other;
	m_acceleration *= MAX_ACCELERATION / sqrt(m_acceleration.x * m_acceleration.x + m_acceleration.y * m_acceleration.y);
}

void Abductor::chaseAstronaut(AlienManager * data) {
	auto astronauts = data->getAstronauts();
	if (!m_chasing) {
		bool foundNewTarget;
		int closestIndex;
		float closestDistSqr = std::numeric_limits<float>::max();
		for (int i = 0; i < astronauts->size(); i++) {
			sf::Vector2f d = astronauts->at(i).getPos() - m_position;
			float distSqr = d.x * d.x + d.y * d.y;
			if (distSqr > CHASE_DISTANCE * CHASE_DISTANCE) {
				if (closestDistSqr > distSqr) {
					closestDistSqr = distSqr;
					closestIndex = i;
					foundNewTarget = true; 
				}
			}
		}
		if (foundNewTarget) {
			if (std::find(m_chasedIndices.begin(), m_chasedIndices.end(), closestIndex) != m_chasedIndices.end()) {
				m_chasedIndices.push_back(closestIndex);
				m_chaseIndex = closestIndex;
			}
		}
	}
}
