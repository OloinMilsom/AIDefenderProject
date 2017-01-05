#pragma once

#include "stdafx.h"
#include "Terrain.h"
#include "AlienManager.h"

class Astronaut {
private:

	const float X_SPEED = 70.0f;

	sf::Vector2f m_position;
	sf::RectangleShape m_sprite;
	float m_vel;
	int avoidTarget;
	AlienManager * m_alienManager;
public:
	Astronaut(float x, AlienManager * alienManager);
	void update(float dt, Terrain * terrain);
	void render(sf::RenderWindow * window, Camera * camera);
	void avoid();
	void wander();
	bool isAlienNear();
};