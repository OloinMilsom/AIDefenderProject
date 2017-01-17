#include "Player.h"

Player::Player() : m_xVel(0) {
	for (int i = 0; i < 4; i++) {
		m_keyDowns[i] = false;
	}
	m_sprite = sf::RectangleShape(sf::Vector2f(20, 10));
	m_sprite.setFillColor(sf::Color::Red);
	m_movingRight = true;
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

	for (int i = 0; i < BulletManager::getInstance()->getSize(); i++)
	{
		if (BulletManager::getInstance()->checkCollision(i, m_sprite) && BulletManager::getInstance()->getIsEnemyBullet(i))
		{
			//Do bullet collisions
		}
	}
	

	m_pos.x += m_xVel * dt;
	m_sprite.setPosition(m_pos);
}

void Player::render(sf::RenderWindow * window, Camera * camera) {
	sf::RectangleShape temp = m_sprite;
	temp.setPosition((*camera) + temp.getPosition());
	window->draw(temp);
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
			m_movingRight = false; 
			break;
		case sf::Keyboard::S:
			m_keyDowns[2] = true;
			break;
		case sf::Keyboard::D:
			m_keyDowns[3] = true;
			m_movingRight = true;
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

sf::Vector2f Player::getPosition() const {
	return m_pos;
}

void Player::setPosition(sf::Vector2f val) {
	m_pos = val;
}

bool Player::getDirection()
{
	return m_movingRight;
}

bool Player::Collide(sf::RectangleShape rect)
{
	return m_sprite.getTextureRect().intersects(rect.getTextureRect());
}

bool Player::Collide(sf::CircleShape circ)
{
	return m_sprite.getTextureRect().intersects(circ.getTextureRect());
}

bool Player::Collide(sf::Vertex vert)
{
	return false;
}
