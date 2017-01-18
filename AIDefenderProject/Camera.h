#pragma once
#include "stdafx.h"

//! Camera transform class
/*!
Transforms vectors and sprites into camera coordinates so that rendering can
be based on player position
*/
class Camera {
private:
	sf::Vector2f m_transform;
	sf::Vector2f m_screenCentre;
	sf::Vector2f m_worldSize;
public:
	Camera(int screenWidth = 0, int screenHeight = 0, int worldWidth = 0, int worldHeight = 0); //!< Camera constructor
	
	//! updates the camera
	/*!
	\param centre the new centre of the screen
	*/
	void update(sf::Vector2f centre); 

	sf::Vector2f operator+(sf::Vector2f vec) const; //!< transforms a vector into Camera coords
	sf::Sprite operator+(sf::Sprite spr); //!< transforms a sprite into Camera coords
};