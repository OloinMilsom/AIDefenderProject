#include "PowerupManager.h"


PowerupManager::PowerupManager()
{
	m_startTime = m_clock.getElapsedTime();
	m_powerups.push_back(Powerup(0));
}

PowerupManager::PowerupManager(Player* player)
{
	m_player = player;
	m_startTime = m_clock.getElapsedTime();
	m_powerups.push_back(Powerup(0));
}


PowerupManager::~PowerupManager()
{
}

void PowerupManager::addPowerup(int type)
{
	bool needNew = true; //Temorary bool to check if a new powerup is needed
	
	for (int i = 0; i < m_powerups.size(); i++) //for the size of the powerup vector
	{
	if (!m_powerups.at(i).getAlive())
		{
			m_powerups.at(i).reset(type);
			needNew = false; //Don't need a new powerup
			break; //loop is no longer needed
		}
	}
	if (needNew)
	{
		m_powerups.push_back(type); //Adds a powerup to the vector
	}

}

void PowerupManager::update()
{
	for (int i = 0; i < m_powerups.size(); i++)
	{
		//if (m_player->Collide(m_powerups.at(i).getRect()))
		//{
		//	m_powerups.at(i).trigger();
		//	if (m_powerups.at(i).getType() == 0)
		//	{
		//		m_player->giveHyperJump();
		//	}
		//	else
		//	{
		//		//other powerup
		//	}
		//}
	}

	if (m_clock.getElapsedTime() - m_startTime > m_interval)
	{
		m_startTime = m_clock.getElapsedTime();
		addPowerup(rand() % 2);
	}
}


void PowerupManager::render(sf::RenderWindow * window, Camera * camera)
{
	for (int i = 0; i < m_powerups.size(); i++)
	{
		m_powerups.at(i).render(window, camera);
	}
}
