#include "Player.h"

Player::Player() : m_xVel(0) {
	for (int i = 0; i < 4; i++) {
		m_keyDowns[i] = false;
	}

	m_tex.loadFromFile("Resources/Player.png");
	m_sprite = sf::Sprite(m_tex, sf::IntRect(0, 0, m_tex.getSize().x / 2, m_tex.getSize().y));
	m_sprite.setOrigin(m_tex.getSize().x / 4, m_tex.getSize().y / 2);

	m_movingRight = true;
	m_canHyperJump = true;
	m_canFire = true;

	m_pos = sf::Vector2f(400, 300);
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
	m_sprite.setTextureRect(sf::IntRect(abs(static_cast<int>(m_pos.x / 15) % 2) * (m_tex.getSize().x / 2), 0, m_tex.getSize().x / 2, m_tex.getSize().y));
	if (m_xVel > 0.1f) {
		m_sprite.setScale(1, 1);
	}
	else if (m_xVel < -0.1f) {
		m_sprite.setScale(-1, 1);
	}
	m_sprite.setPosition(m_pos);
}

void Player::render(sf::RenderWindow * window, Camera * camera) {
	window->draw((*camera) + m_sprite);
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
		case sf::Keyboard::Q:
			hyperJump();
			break;
			break;
		case sf::Keyboard::Space:
			if (m_canFire)
			{
				if (getDirection())
				{
					BulletManager::getInstance()->addBullet(getPosition(), sf::Vector2f(15.0f, 0), false); //Moving Right
				}
				else
				{
					BulletManager::getInstance()->addBullet(getPosition(), sf::Vector2f(-15.0f, 0), false); //Moving Left
				}
				m_canFire = false;
			}

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
		case sf::Keyboard::Space:
			m_canFire = true;
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

const sf::Vector2f * Player::getPosPointer() const
{
	return &m_pos;
}

void Player::setPosition(sf::Vector2f val) {
	m_pos = val;
}

void Player::hyperJump()
{
	if (m_canHyperJump)
	{
		m_pos = sf::Vector2f(rand() % (800 * 9), rand() % 600);
		m_canHyperJump = false;
	}
}

void Player::hit()
{
	m_health--;
}

void Player::giveHyperJump()
{
	m_canHyperJump = true;
}

bool Player::getDirection()
{
	return m_movingRight;
}

int Player::getHealth()
{
	return m_health;
}

sf::Sprite Player::getSprite()
{
	return m_sprite;
}
