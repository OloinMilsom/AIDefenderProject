#pragma once

#include "stdafx.h"
#include "Terrain.h"
#include "AlienManager.h"
#include <limits>

class AlienManager;

class Astronaut {
private:
	const float X_SPEED = 70.0f;
	const AlienManager * m_alienManager;

	sf::Vector2f m_position;

	sf::Texture m_tex;
	sf::Sprite m_sprite;

	float m_vel;
	int avoidTarget;
	bool m_beingAbducted;
	bool m_alive;

public:
	Astronaut(float x = 0, AlienManager * alienManager = nullptr);
	void update(float dt, Terrain * terrain);
	void render(sf::RenderWindow * window, Camera * camera);
	void avoid();
	void wander();
	bool isAlienNear();
	sf::Vector2f getPos() const;
	bool getAlive() const;
	void setPos(sf::Vector2f val);
	void setBeingAbducted(bool val);
	void setAlive(bool val);
};