#include "Player.h"

Player::Player() : m_xVel(0) {
	for (int i = 0; i < 4; i++) {
		m_keyDowns[i] = false;
	}
	m_sprite = sf::RectangleShape(sf::Vector2f(20, 10));
	m_sprite.setFillColor(sf::Color::Red);
}

void Player::update(float dt) {
	if (m_keyDowns[0]) { // W key held
		m_pos.y -= Y_SPEED * dt;
	}
	if (m_keyDowns[1]) { // A key held
		if (m_xVel > 0) {
			m_xVel = 0;
		}
		else {
			if (m_xVel > -MAX_X_VEL) {
				m_xVel -= X_ACCEL * dt;
			}
		}
	}
	if (m_keyDowns[2]) { // S key held
		m_pos.y += Y_SPEED * dt;
	}
	if (m_keyDowns[3]) { // D key held
		if (m_xVel < 0) {
			m_xVel = 0;
		}
		else {
			if (m_xVel < MAX_X_VEL) {
				m_xVel += X_ACCEL * dt;
			}
		}
	}

	if (!m_keyDowns[1] && !m_keyDowns[3]) {
		if (fabsf(m_xVel) > 1) {
			m_xVel < 0 ? m_xVel += X_ACCEL * dt : m_xVel -= X_ACCEL * dt;
		}
		else {
			m_xVel = 0;
		}
	}

	m_pos.x += m_xVel * dt;
	m_sprite.setPosition(m_pos);
}

void Player::render(sf::RenderWindow * window) {
	window->draw(m_sprite);
}

void Player::onEvent(sf::Event evt) {
	switch (evt.type) {
	case sf::Event::KeyPressed:
		switch (evt.key.code) {
		case sf::Keyboard::W:
			m_keyDowns[0] = true;
			break; 
		case sf::Keyboard::A:
			m_keyDowns[1] = true;
			break;
		case sf::Keyboard::S:
			m_keyDowns[2] = true;
			break;
		case sf::Keyboard::D:
			m_keyDowns[3] = true;
			break;
		default:
			break;
		}
		break;

	case sf::Event::KeyReleased:
		switch (evt.key.code) {
		case sf::Keyboard::W:
			m_keyDowns[0] = false;
			break;
		case sf::Keyboard::A:
			m_keyDowns[1] = false;
			break;
		case sf::Keyboard::S:
			m_keyDowns[2] = false;
			break;
		case sf::Keyboard::D:
			m_keyDowns[3] = false;
			break;
		default:
			break;
		}

	default:
		break;
	}
}
