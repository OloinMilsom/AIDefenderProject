#pragma once
#include "stdafx.h"
#include "EventListener.h"
#include "Camera.h"
#include "BulletManager.h"

//! Player class
/*!
Player is controlled by the user using WASD keys. The player can fire lasers to kill
Aliens as well as activating smart bombs and hyperjumps. Smart bombs kill everything
on screen but takes a minute to recharge. The hyperjump moves the player to a random
location.
*/
class Player : public EventListener {
private:
	// consts in pixels and seconds
	const float MAX_X_VEL = 300.0f;
	const float X_ACCEL = 200.0f;
	const float Y_SPEED = 100.0f;

	sf::Vector2f m_pos;

	sf::Texture m_tex;
	sf::Sprite m_sprite;

	int m_health;

	bool m_keyDowns[4]; // 0 = W, 1 = A, 2 = S, 3 = D
	bool m_movingRight;
	bool m_canHyperJump;
	bool m_canFire;

	float m_xVel;
public:
	Player(); //!< Player constructor
	void update(float dt); // Player update using delta time from last frame

	//! Player render function
	/*!
	\param window SFML window to render to
	\param camera adjusts positions based on the camera position
	draws the player to the screen
	*/
	void render(sf::RenderWindow * window, Camera * camera);

	void onEvent(sf::Event evt); //!< Player event response function
	sf::Vector2f getPosition() const; //!< Player position vector accessor
	const sf::Vector2f* getPosPointer() const; //!< Player position vector as pointer accessor
	void setPosition(sf::Vector2f); //!< Player position vector setter
	void hyperJump(); //!< Player use a hyperjump
	void hit();
	void giveHyperJump(); //!< Give Player a hyperjump use
	bool getDirection(); //!< Get the Player direction
	int getHealth();
	sf::Sprite getSprite();
};