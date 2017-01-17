#pragma once

#include "stdafx.h"
#include "Camera.h"
#include "AlienManager.h"

class AlienManager;
class Terrain;

enum AlienType {
	nest,
	abductor,
	mutant
};

class Alien {
protected:
	const float MAX_SPEED;
	const float MAX_ACCELERATION = 5.0f;

	bool m_alive;
	AlienType m_type;
	sf::RectangleShape m_sprite;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	float m_angle;

	void move(float dt);
	void wander();
	void avoidBounds(const Terrain * terrain);
public:
	Alien(sf::Vector2f pos, float speed, float acceleration);
	virtual void update(float dt, AlienManager * data) = 0;
	void render(sf::RenderWindow * window, Camera * camera);
	sf::Vector2f getPos();
	sf::Vector2f getVel();
	sf::Vector2f getAccel();
	sf::RectangleShape getRect();
	AlienType getType();
};