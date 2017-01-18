#pragma once

#include "stdafx.h"
#include <deque>
#include "Alien.h"
#include "Astronaut.h"
#include "Player.h"
#include "MiniMap.h"


class Alien;
class Astronaut;
class MiniMap;
enum AlienType;

//! Manages Alien objects
/*!
Manages the creation, deletion, updating and rendering of all Alien objects. Provides
an interface to all aliens for other classes. Contains pointers to game data for
Alien update.
*/
class AlienManager {
private:
	std::deque<Alien *> m_aliens;	// aliens will be ordered such that nests will come first,
									// abductors will be in the middle and mutants will be at the end.
									// counts will be kept so that iterators to each of these points is accessable
	
	std::vector<Astronaut> * m_astronauts;// game data pointers stored here so the aliens can respond
	const Player * m_player;					// to this data in their behaviours, stored as const to ensure 
	const Terrain * m_terrain;					// aliens do not alter this data as it is not their responsibility
	const Camera * m_camera;

	int m_nestCount;		// alien counts used to get the correct iterators for each type
	int m_abductorCount;
	int m_mutantCount;

	std::vector<std::pair<AlienType, sf::Vector2f>> m_additionStage;	// addition stage prevents invalid iterators being created
																		// from addition into the alien container

	void clearAdditionStage();	// this container holds any additions until iteration through the alien list concludes

	MiniMap * m_map;

public:
	//! AlienManager constructor
	/*!
		\param player pointer for Player game data		
		\param astronauts pointer for Astronaut game data
		\param terrain pointer for Terrain game data
		\param camera pointer for Camera game data
	*/
	AlienManager(Player * player, std::vector<Astronaut> * astronauts, Terrain * terrain, Camera * camera);
	~AlienManager(); //!< AlienManager destructor

	const std::deque<Alien *> getAll() const; //!< get the Alien container
	std::deque<Alien *> * getAlienPointer();

	std::deque<Alien *>::iterator nestBegin(); //!< get the start iterator for AlienNest
	std::deque<Alien *>::iterator nestEnd(); //!< get the end iterator for AlienNest
	std::deque<Alien *>::iterator abductorBegin(); //!< get the start iterator for Abductor
	std::deque<Alien *>::iterator abductorEnd(); //!< get the end iterator for Abductor
	std::deque<Alien *>::iterator mutantBegin(); //!< get the start iterator for Mutant
	std::deque<Alien *>::iterator mutantEnd(); //!< get the end iterator for Mutant

	std::vector<Astronaut> * getAstronauts(); //!< get the Astronaut game data
	const Player * getPlayer(); //!< get the Player game data
	const Terrain * getTerrain(); //!< get the Terrain game data
	const Camera * getCamera(); //!< get the Camera game data

	void addNest(sf::Vector2f position); //!< adds an AlienNest to Alien container
	void addAbductor(sf::Vector2f position); //!< adds an Abductor to Alien container
	void addMutant(sf::Vector2f position); //!< adds an Mutant to Alien container

	//! Updates all the Alien objects
	/*!
	\param dt delta time since last frame
	*/
	void update(float dt);

	//! Renders all the Alien objects
	/*!
	\param window SFML window to render to
	\param camera adjusts positions based on the camera position
	draws Alien to the screen
	*/
	void render(sf::RenderWindow * window, Camera * camera);
};