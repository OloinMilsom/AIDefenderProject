#pragma once

#include "stdafx.h"
#include "Camera.h"
#include "AlienManager.h"
#include "BulletManager.h"

class AlienManager;
class Terrain;

//! Alien type to be distinguished at run time
enum AlienType {
	nest,
	abductor,
	mutant
};

//! Alien base class
/*!
Pure virtual Alien base class for the alien hierarchy tree. Implements the common
elements of all aliens and has a pure virtual update function to allow for different
Alien behaviours.
*/
class Alien {
protected:
	const float MAX_SPEED;
	const float MAX_ACCELERATION = 5.0f;

	bool m_alive;
	AlienType m_type;

	sf::Texture m_tex;
	sf::Sprite m_sprite;

	sf::Vector2f m_position;
	sf::Vector2f m_velocity;
	sf::Vector2f m_acceleration;
	float m_angle;
	int m_health;

	void move(float dt);
	void wander();
	void avoidBounds(const Terrain * terrain);
public:
	Alien(sf::Vector2f pos, float speed, float acceleration); //!< Alien constructor
	void hit();
	//! Unimplemented Alien update
	/*!
	\param dt delta time since last frame
	\param data pointer allows abductor access to game data
	*/
	virtual void update(float dt, AlienManager * data) = 0;

	//! Alien render function
	/*!
	\param window SFML window to render to
	\param camera adjusts positions based on the camera position
	draws Alien to the screen
	*/
	void render(sf::RenderWindow * window, Camera * camera);

	sf::Vector2f getPos(); //!< returns the Alien position
	sf::Vector2f getVel(); //!< returns the Alien velocity
	sf::Vector2f getAccel(); //!< returns the Alien acceleration
	sf::Sprite getSprite();
	AlienType getType(); //!< returns the Type of the Alien
};