#pragma once

#include "stdafx.h"
#include <deque>
#include "Alien.h"

#include "Astronaut.h"
#include "Player.h"

class Alien;
enum AlienType;

class AlienManager {
private:
	std::deque<Alien *> m_aliens;	// aliens will be ordered such that nests will come first,
									// abductors will be in the middle and mutants will be at the end.
									// counts will be kept so that iterators to each of these points is accessable
	
	const std::vector<Astronaut> * m_astronauts;// game data pointers stored here so the aliens can respond
	const Player * m_player;					// to this data in their behaviours, stored as const to ensure 
	const Terrain * m_terrain;					// aliens do not alter this data as it is not their responsibility
	const Camera * m_camera;

	int m_nestCount;		// alien counts used to get the correct iterators for each type
	int m_abductorCount;
	int m_mutantCount;

	std::vector<std::pair<AlienType, sf::Vector2f>> m_additionStage;	// addition stage prevents invalid iterators being created
																		// from addition into the alien container

	void clearAdditionStage();	// this container holds any additions until iteration through the alien list concludes

public:
	// constructor/destructor
	AlienManager(Player * player, std::vector<Astronaut> * astronauts, Terrain * terrain, Camera * camera);
	~AlienManager();

	// get all the aliens
	const std::deque<Alien *> getAll();

	// iterators to access different alien types;
	std::deque<Alien *>::iterator nestBegin();
	std::deque<Alien *>::iterator nestEnd();
	std::deque<Alien *>::iterator abductorBegin();
	std::deque<Alien *>::iterator abductorEnd();
	std::deque<Alien *>::iterator mutantBegin();
	std::deque<Alien *>::iterator mutantEnd();

	// get the game data for alien behaviours
	const std::vector<Astronaut> * getAstronauts();
	const Player * getPlayer();
	const Terrain * getTerrain();
	const Camera * getCamera();

	// add aliens to the addition stage
	void addNest(sf::Vector2f position);
	void addAbductor(sf::Vector2f position);
	void addMutant(sf::Vector2f position);

	// update and render
	void update(float dt);
	void render(sf::RenderWindow * window, Camera * camera);
};