#pragma once
#include "stdafx.h"
#include "EventListener.h"

class Player : public EventListener {
private:
	// consts in pixels and seconds
	const float MAX_X_VEL = 300.0f;
	const float X_ACCEL = 200.0f;
	const float Y_SPEED = 100.0f;

	sf::Vector2f m_pos;
	sf::RectangleShape m_sprite;
	bool m_keyDowns[4]; // 0 = W, 1 = A, 2 = S, 3 = D
	float m_xVel;
public:
	Player();
	void update(float dt);
	void render(sf::RenderWindow * window);
	void onEvent(sf::Event evt);
	sf::Vector2f getPosition() const;
	void setPosition(sf::Vector2f);
};