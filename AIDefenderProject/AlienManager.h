#pragma once

#include "stdafx.h"

#include "Alien.h"

#include "Astronaut.h"
#include "Player.h"

class Alien;

class AlienManager {
private:
	std::vector<Alien *> m_aliens;
	const std::vector<Astronaut> * m_astronauts;
	const Player * m_player;

public:
	AlienManager(Player * player, std::vector<Astronaut> * astronauts);
	~AlienManager();

	std::vector<Alien *> * getAll();
	std::vector<Alien *> * getNests();
	std::vector<Alien *> * getAbductors();
	std::vector<Alien *> * getMutants();

	const std::vector<Astronaut> * getAstronauts();
	const Player * getPlayer();

	void addNest(sf::Vector2f position);
	void addAbductor(sf::Vector2f position);
	void addMutant(sf::Vector2f position);

	void update(float dt);
	void render(sf::RenderWindow * window, Camera * camera);
};