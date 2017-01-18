#pragma once
#include "stdafx.h" 
#include "Camera.h"

//! Powerup class
/*!
Powerup for player to collect and use
*/
class Powerup
{
protected:
	//sf::Vector2f m_pos; //Position of powerup
	sf::Texture m_tex;
	sf::Sprite m_sprite;
	bool m_alive; //Is the powerup currently active
	int m_type; //0 = hyperjump charge
public:
	Powerup(int); //!< Powerup constructor
	~Powerup(); //!< Powerup destructor

	//! Powerup render function
	/*!
	\param window SFML window to render to
	\param camera adjusts positions based on the camera position
	draws the powerup to the screen
	*/
	void render(sf::RenderWindow * window, Camera * camera); 

	void reset(int); //!< resets the Powerup
	void trigger(); //!< triggers the Powerup after collision
	bool getAlive(); //!< Powerup alive bool accessor
	int getType(); //!< Powerup type accessor
	sf::Sprite getSprite(); //!< Powerup sprite accessor
};

