#include "AlienManager.h"
#include "AlienNest.h"
#include "Abductor.h"
#include "Mutant.h"

#pragma region Constructor/Destructor

AlienManager::AlienManager(Player * player, std::vector<Astronaut>* astronauts, Terrain * terrain, Camera * camera)
	:m_player(player), 
	 m_astronauts(astronauts),
	 m_terrain(terrain),
	 m_camera(camera),
	 m_map(&m_aliens, astronauts, player){
}

AlienManager::~AlienManager() {
	for (auto iter = m_aliens.begin(); iter != m_aliens.end(); iter++) {
		delete (*iter);
	}
	m_aliens.clear();
}

#pragma endregion

#pragma region ContainerOperators

const std::deque<Alien*> AlienManager::getAll() const {
	return m_aliens;
}

std::deque<Alien*>* AlienManager::getAlienPointer()
{
	return &m_aliens;
}

std::deque<Alien*>::iterator AlienManager::nestBegin() {
	return m_aliens.begin();
}

std::deque<Alien*>::iterator AlienManager::nestEnd() {
	return m_aliens.begin() + m_nestCount;
}

std::deque<Alien*>::iterator AlienManager::abductorBegin() {
	return m_aliens.begin() + m_nestCount;
}

std::deque<Alien*>::iterator AlienManager::abductorEnd() {
	return m_aliens.begin() + m_nestCount + m_abductorCount;
}

std::deque<Alien*>::iterator AlienManager::mutantBegin() {
	return m_aliens.begin() + m_nestCount + m_abductorCount;
}

std::deque<Alien*>::iterator AlienManager::mutantEnd() {
	return m_aliens.end();
}

#pragma endregion

#pragma region GameDataAccessors

std::vector<Astronaut> * AlienManager::getAstronauts() {
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

#pragma endregion

#pragma region AlienAddition

void AlienManager::clearAdditionStage() {
	for (int i = 0; i < m_additionStage.size(); i++) {
		switch (m_additionStage[i].first) {
		case AlienType::nest:
			m_aliens.insert(nestEnd(), new AlienNest(m_additionStage[i].second, 170, 250));
			m_nestCount++;
			break;
		case AlienType::abductor:
			if (m_abductorCount < 20) {
				m_aliens.insert(abductorEnd(), new Abductor(m_additionStage[i].second, 170, 450));
				m_abductorCount++;
			}
			break;
		case AlienType::mutant:
			m_aliens.insert(mutantEnd(), new Mutant(m_additionStage[i].second, 150, 450));
			m_mutantCount++;
			break;
		}
	}
	m_additionStage.clear();
}

void AlienManager::addNest(sf::Vector2f position) {
	m_additionStage.push_back(std::make_pair(AlienType::nest, position));
}

void AlienManager::addAbductor(sf::Vector2f position) {
	m_additionStage.push_back(std::make_pair(AlienType::abductor, position));
}

void AlienManager::addMutant(sf::Vector2f position) {
	m_additionStage.push_back(std::make_pair(AlienType::mutant, position));
}

#pragma endregion

#pragma region Update/Render

void AlienManager::update(float dt) {
	//for (int i = 0; i < m_aliens.size(); i++) //m_player is const, meaning i cant edit it. Must change this for collisions
	//{
	//	if (m_player->Collide(m_aliens.at(i)->getRect()))
	//	{

	//	}
	//}

	for (auto iter = m_aliens.begin(); iter != m_aliens.end(); iter++) {
		(*iter)->update(dt, this);
	}
	clearAdditionStage();
}

void AlienManager::render(sf::RenderWindow * window, Camera * camera) {
	for (auto iter = m_aliens.begin(); iter != m_aliens.end(); iter++) {
		(*iter)->render(window, camera);
	}
	m_map.render(window, m_nestCount, m_abductorCount, m_mutantCount);
}

#pragma endregion