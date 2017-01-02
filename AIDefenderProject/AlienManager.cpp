#include "AlienManager.h"
#include "AlienNest.h"
#include "Abductor.h"
#include "Mutant.h"

AlienManager::AlienManager(Player * player, std::vector<Astronaut>* astronauts) : m_player(player), m_astronauts(astronauts) {
}

AlienManager::~AlienManager() {
	for (int i = 0; i < m_aliens.size(); i++) {
		delete m_aliens[i];
	}
	m_aliens.clear();
}

void AlienManager::addNest(sf::Vector2f position) {
	m_aliens.push_back(new AlienNest(position, 70));
}

void AlienManager::update(float dt) {
	for (int i = 0; i < m_aliens.size(); i++) {
		m_aliens[i]->update(dt, this);
	}
}

void AlienManager::render(sf::RenderWindow * window, Camera * camera) {
	for (int i = 0; i < m_aliens.size(); i++) {
		m_aliens[i]->render(window, camera);
	}
}
