#pragma once
#include "stdafx.h" 
#include "Powerup.h"
#include "Player.h"

//! PowerupManager class
/*!
In charge of the creation, deletion and management of powerups in the game
*/
class PowerupManager
{
private:
	std::vector<Powerup> m_powerups;
	sf::Clock m_clock; //Clock for getting current time
	sf::Time m_startTime; //Time that the bullet is created or reset
	sf::Time m_interval = sf::seconds(10.0f); 
	Player * m_player;
public:
	PowerupManager(); //!< PowerupManager constructor
	PowerupManager(Player*); //!< PowerupManager constructor taking player by pointer
	~PowerupManager(); //!< PowerupManager destructor

	void addPowerup(int); //!< creates and adds a Powerup to the game
	void update(); //!< updates all powerups

	//! PowerupManager render function
	/*!
	\param window SFML window to render to
	\param camera adjusts positions based on the camera position
	draws all the powerups to the screen
	*/
	void render(sf::RenderWindow * window, Camera * camera);
};

