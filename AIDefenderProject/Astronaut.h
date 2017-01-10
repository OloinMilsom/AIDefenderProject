#pragma once

#include "stdafx.h"
#include "Terrain.h"
#include "AlienManager.h"

class AlienManager;

class Astronaut {
private:
	const float X_SPEED = 70.0f;
	const AlienManager * m_alienManager;

	sf::Vector2f m_position;
	sf::RectangleShape m_sprite;
	float m_vel;
	int avoidTarget;

public:
	Astronaut(float x = 0, AlienManager * alienManager = nullptr);
	void update(float dt, Terrain * terrain);
	void render(sf::RenderWindow * window, Camera * camera);
	void avoid();
	void wander();
	bool isAlienNear();
	sf::Vector2f getPos() const;
};