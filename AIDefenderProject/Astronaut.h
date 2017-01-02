#pragma once

#include "stdafx.h"
#include "Terrain.h"

class Astronaut {
private:

	const float X_SPEED = 70.0f;

	sf::Vector2f m_position;
	sf::RectangleShape m_sprite;
	float m_vel;
public:
	Astronaut(float x);
	void update(float dt, Terrain * terrain);
	void render(sf::RenderWindow * window, Camera * camera);
};