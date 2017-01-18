#pragma once
#include "stdafx.h"
#include "Obstacle.h"

class ObstacleManager
{
private:
	std::vector<Obstacle> m_obstacles;
public:
	ObstacleManager();
	~ObstacleManager();

	void update();
	void render(sf::RenderWindow * window, Camera * camera);
	std::vector<Obstacle>* getPointer();
};

