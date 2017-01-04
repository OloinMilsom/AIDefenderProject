#include "AlienManager.h"
#include "AlienNest.h"
#include "Abductor.h"
#include "Mutant.h"

AlienManager::AlienManager(Player * player, std::vector<Astronaut>* astronauts, Terrain * terrain, Camera * camera) 
	:m_player(player), 
	 m_astronauts(astronauts),
	 m_terrain(terrain),
	 m_camera(camera){
}

AlienManager::~AlienManager() {
	for (int i = 0; i < m_aliens.size(); i++) {
		delete m_aliens[i];
	}
	m_aliens.clear();
}

const std::vector<Astronaut>* AlienManager::getAstronauts() {
	return m_astronauts;
}

const Player * AlienManager::getPlayer() {
	return m_player;
}

const Terrain * AlienManager::getTerrain() {
	return m_terrain;
}

const Camera * AlienManager::getCamera() {
	return m_camera;
}

void AlienManager::addNest(sf::Vector2f position) {
	m_aliens.push_back(new AlienNest(position, 170, 150));
}

void AlienManager::addAbductor(sf::Vector2f position) {
	// to be implemented with abductors
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
