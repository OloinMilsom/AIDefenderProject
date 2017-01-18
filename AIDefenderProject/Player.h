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

	sf::Texture m_tex;
	sf::Sprite m_sprite;

	int m_health;

	bool m_keyDowns[4]; // 0 = W, 1 = A, 2 = S, 3 = D
	bool m_movingRight;
	bool m_canHyperJump;
	bool m_canFire;

	float m_xVel;
public:
	Player();
	void update(float dt);
	void render(sf::RenderWindow * window, Camera * camera);
	void onEvent(sf::Event evt);
	sf::Vector2f getPosition() const;
	const sf::Vector2f* getPosPointer() const;
	void setPosition(sf::Vector2f);
	void hyperJump();
	void hit();
	void giveHyperJump();
	bool getDirection();
	int getHealth();
	sf::Sprite getSprite();
};