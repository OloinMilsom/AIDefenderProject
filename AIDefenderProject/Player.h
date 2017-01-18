#pragma once
#include "stdafx.h"
#include "EventListener.h"
#include "Camera.h"
#include "BulletManager.h"

class Player : public EventListener {
private:
	// consts in pixels and seconds
	const float MAX_X_VEL = 300.0f;
	const float X_ACCEL = 200.0f;
	const float Y_SPEED = 100.0f;

	sf::Vector2f m_pos;
	sf::RectangleShape m_sprite;
	bool m_keyDowns[4]; // 0 = W, 1 = A, 2 = S, 3 = D
	bool m_movingRight;
	bool m_canHyperJump;
	bool m_canSmartBomb;
	sf::Clock m_clock; //Clock for getting current time
	sf::Time m_lastBombUsed; //Time that the bullet is created or reset
	sf::Time m_bombCooldown = sf::seconds(60.0f);
	float m_xVel;
public:
	Player();
	void update(float dt);
	void render(sf::RenderWindow * window, Camera * camera);
	void onEvent(sf::Event evt);
	sf::Vector2f getPosition() const;
	const sf::Vector2f* getPosPointer() const;
	void setPosition(sf::Vector2f);
	void smartBomb();
	void hyperJump();
	void giveHyperJump();
	bool getDirection();
	bool Collide(sf::RectangleShape);
	bool Collide(sf::CircleShape);
	bool Collide(sf::Vertex);
};