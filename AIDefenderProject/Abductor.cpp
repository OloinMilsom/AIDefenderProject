#include "Abductor.h"

std::vector<int> Abductor::m_chasedIndices;

Abductor::Abductor(sf::Vector2f position, float speed, float acceleration) : Alien(position, speed, acceleration), m_inFlock(false), m_chasing(false), m_abducting(false) {
	m_type = AlienType::abductor;

	m_health = 1;

	m_angle = acos(-1) * 2 * static_cast<float>(rand()) / static_cast<float>(RAND_MAX);
	m_acceleration = sf::Vector2f(cos(m_angle), sin(m_angle)) * MAX_ACCELERATION;

	m_tex.loadFromFile("Resources/Abductor.png");
	m_sprite = sf::Sprite(m_tex, sf::IntRect(0, 0, m_tex.getSize().x / 6, m_tex.getSize().y));
	m_sprite.setOrigin(m_tex.getSize().x / 12, m_tex.getSize().y / 2);
}

void Abductor::update(float dt, AlienManager * data) {
	if (!m_chasing) {
		flock(data);
		wander();
	}
	if (!m_abducting) {
		avoidBounds(data->getTerrain());
	}
	chaseAstronaut(data);

	m_sprite.setTextureRect(sf::IntRect(abs(static_cast<int>(m_position.x / 15) % 6) * (m_tex.getSize().x / 6.0f), 0, m_tex.getSize().x / 6.0f, m_tex.getSize().y));
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
		bool foundNewTarget = false;
		int closestIndex;
		float closestDistSqr = std::numeric_limits<float>::max();
		for (int i = 0; i < astronauts->size(); i++) {
			sf::Vector2f d = ((*data->getCamera()) + astronauts->at(i).getPos()) - ((*data->getCamera()) + m_position);
			float distSqr = d.x * d.x + d.y * d.y;
			if (distSqr < CHASE_DISTANCE * CHASE_DISTANCE) {
				if (closestDistSqr > distSqr && astronauts->at(i).getAlive()) {
					closestDistSqr = distSqr;
					closestIndex = i;
					foundNewTarget = true; 
				}
			}
		}
		if (foundNewTarget) {
			if (std::find(m_chasedIndices.begin(), m_chasedIndices.end(), closestIndex) == m_chasedIndices.end()) {
				m_chasedIndices.push_back(closestIndex);
				m_chaseIndex = closestIndex;
				m_chasing = true;
			}
		}
	}
	else {
		if (!m_abducting) {
			m_acceleration = ((*data->getCamera()) + astronauts->at(m_chaseIndex).getPos()) - ((*data->getCamera()) + m_position);
			m_acceleration /= sqrt(m_acceleration.x * m_acceleration.x + m_acceleration.y * m_acceleration.y);

			sf::Vector2f d = ((*data->getCamera()) + astronauts->at(m_chaseIndex).getPos()) - ((*data->getCamera()) + m_position);
			if (d.x * d.x + d.y * d.y < ABDUCT_DISTANCE * ABDUCT_DISTANCE) {
				m_abducting = true;
				m_velocity = sf::Vector2f(0, -15);
				m_acceleration = sf::Vector2f(0, 0);
				astronauts->at(m_chaseIndex).setBeingAbducted(true);
			}
		}
		else {
			m_velocity = sf::Vector2f(0, -ABDUCT_SPEED);
			m_acceleration = sf::Vector2f(0, 0);
			astronauts->at(m_chaseIndex).setPos(m_position);
			if (m_position.y < 0) {
				m_chasing = false;
				m_abducting = false;
				data->addMutant(m_position);
				astronauts->at(m_chaseIndex).setAlive(false);
				std::remove(m_chasedIndices.begin(), m_chasedIndices.end(), m_chaseIndex);
			}
		}
	}
}
