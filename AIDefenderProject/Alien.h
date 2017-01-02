#pragma once

#include "stdafx.h"
#include "Camera.h"
#include "AlienManager.h"

class AlienManager;

class Alien {
protected:
	const float SPEED;

	sf::RectangleShape m_sprite;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	float m_angle;
public:
	Alien(sf::Vector2f pos, float speed);
	virtual void update(float dt, AlienManager * data) = 0;
	void render(sf::RenderWindow * window, Camera * camera);
};