#pragma once

#include "stdafx.h"
#include "Terrain.h"
#include "AlienManager.h"
#include <limits>

class AlienManager;

//! Astronaut class
/*!
Astronauts wander around the game floor, avoiding aliens. If they are abducted and brought
to the top of the screen they can become mutants.
*/
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
	bool m_falling = false;

public:
	Astronaut(float x = 0, AlienManager * alienManager = nullptr); //!< Astronaut constructor

	//! Astronaut update
	/*!
	\param dt delta time since last fram
	\param terrain the game Terrain for the astronauts to wander on
	*/
	void update(float dt, Terrain * terrain);

	//! Astronaut render function
	/*!
	\param window SFML window to render to
	\param camera adjusts positions based on the camera position
	draws the astronaut to the screen
	*/
	void render(sf::RenderWindow * window, Camera * camera);

	void avoid(); //!< astonaut will avoid nearest alien
	void wander(); //!< astronaut will wander around the game world
	bool isAlienNear(); //!< determines if there is an alien nearby
	sf::Vector2f getPos() const; //!< astronaut position vector accessor
	bool getAlive() const; //!< astronauts alive bool accessor
	void setPos(sf::Vector2f val); //!< astronaut position vector setter
	void setBeingAbducted(bool val); //!< astronaut abducted bool setter
	void setAlive(bool val); //!<astronaut alive bool setter
	void setFalling(bool val);
};