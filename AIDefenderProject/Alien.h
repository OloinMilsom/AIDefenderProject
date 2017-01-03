#pragma once

#include "stdafx.h"
#include "Camera.h"
#include "AlienManager.h"

class AlienManager;

class Alien {
protected:
	const float MAX_SPEED;
	const float MAX_ACCELERATION = 5.0f;

	sf::RectangleShape m_sprite;
	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	float m_angle;
public:
	Alien(sf::Vector2f pos, float speed, float acceleration);
	virtual void update(float dt, AlienManager * data) = 0;
	void render(sf::RenderWindow * window, Camera * camera);
};