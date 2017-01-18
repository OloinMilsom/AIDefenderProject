#include "ObstacleManager.h"



ObstacleManager::ObstacleManager()
{
	for (int i = 0; i < 15; i++)
	{
		m_obstacles.push_back(Obstacle());
	}
}


ObstacleManager::~ObstacleManager()
{
}

void ObstacleManager::update()
{
	for (int i = 0; i < m_obstacles.size(); i++)
	{
		m_obstacles.at(i).update();
	}
}

void ObstacleManager::render(sf::RenderWindow * window, Camera * camera)
{
	for (int i = 0; i < m_obstacles.size(); i++)
	{
		m_obstacles.at(i).render(window, camera);
	}
}

std::vector<Obstacle>* ObstacleManager::getPointer()
{
	return &m_obstacles;
}
