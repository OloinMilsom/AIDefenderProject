#pragma once
#include "stdafx.h" 
#include "Camera.h"

//! Basic Bullet class
/*!
Basic bullet implements it's own behaviour as well as being a starting point
in the bullet hierarchy
*/
class Bullet
{
protected:
	sf::Time lifeSpan = sf::seconds(4.0f); //The lifespan of a bullet

	sf::Vector2f m_pos; //Position of bullet
	sf::Vector2f m_vel; //Velocity of bullet

	sf::Clock m_clock; //Clock for getting current time
	sf::Time m_startTime; //Time that the bullet is created or reset

	sf::Texture m_tex;
	sf::Sprite m_sprite;

	bool m_alive; //Is the bulet currently active
	bool m_isEnemyBullet; //Does this bullet belong to an enemy
public:
	Bullet(sf::Vector2f, sf::Vector2f, bool); //!< Bullet constructor
	~Bullet(); //!< Bullet destructor

	void update(); //!< Bullet update
	sf::Vector2f Normalize(sf::Vector2f); //!< Vector normalise helper

	//! Bullet render function
	/*!
	\param window SFML window to render to
	\param camera adjusts positions based on the camera position
	draws bullet to the screen
	*/
	void render(sf::RenderWindow * window, Camera * camera);
	void hit();

	void reset(sf::Vector2f, sf::Vector2f, bool); //!< resets the bullet
	bool getAlive(); //!< Bullet alive bool accessor
	bool getIsEnemyBullet(); //!< Bullet isEnemyBullet bool accessor
	sf::Vector2f getPos();
	sf::Sprite getSprite();
};

