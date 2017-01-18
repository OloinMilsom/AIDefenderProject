#include "TrackingBullet.h"


TrackingBullet::TrackingBullet(sf::Vector2f pos, sf::Vector2f vel) : Bullet(pos, vel, true)
{
	m_pos = pos;
	m_vel = vel;

	m_tex.loadFromFile("Resources/Missile.png");
	m_sprite = sf::Sprite(m_tex, sf::IntRect(0, 0, m_tex.getSize().x / 2, m_tex.getSize().y));
	m_sprite.setOrigin(m_tex.getSize().x / 4, m_tex.getSize().y / 2);
	//m_sprite.setColor(sf::Color::Red);

	m_alive = true;

	m_isEnemyBullet = true;

	m_startTime = m_clock.getElapsedTime();

	m_sprite.setPosition(m_pos);
}


TrackingBullet::~TrackingBullet()
{
}

void TrackingBullet::reset(sf::Vector2f pos, sf::Vector2f vel)
{
	{
		m_pos = pos;
		m_vel = vel;


		m_alive = true;

		m_isEnemyBullet = true;

		m_startTime = m_clock.getElapsedTime();

		m_sprite.setPosition(m_pos);


	}
}

void TrackingBullet::update(sf::Vector2f pos)
{
	if (m_alive)
	{
		m_vel = -Normalize(m_pos - sf::Vector2f(pos.x, pos.y)); //Sets the velocity to a unit vector in the direction of the target
		m_pos += m_vel;
		m_sprite.setPosition(m_pos);
		if (m_clock.getElapsedTime() - m_startTime > lifeSpan
			&& m_alive == true) // If the bullet has exeeded the lifespan
		{
			m_alive = false; //The bullet is no longet alive
		}
	}

}


sf::Vector2f TrackingBullet::Normalize(sf::Vector2f vec)
{
	float length = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	return sf::Vector2f(vec.x / length, vec.y / length);
}
