#pragma once
#include "stdafx.h" 
#include "Powerup.h"
#include "Player.h"
class PowerupManager
{
private:
	std::vector<Powerup> m_powerups;
	sf::Clock m_clock; //Clock for getting current time
	sf::Time m_startTime; //Time that the bullet is created or reset
	sf::Time m_interval = sf::seconds(10.0f); 
	Player * m_player;
public:
	PowerupManager(Player*);
	~PowerupManager();

	void addPowerup(int);
	void update();
	void render(sf::RenderWindow * window, Camera * camera);
};

