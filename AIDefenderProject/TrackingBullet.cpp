#include "TrackingBullet.h"


TrackingBullet::TrackingBullet(sf::Vector2f pos, sf::Vector2f vel, bool isEnemyBullet) : Bullet(pos, vel, isEnemyBullet)
{
	m_pos = pos;
	m_vel = vel;


	m_alive = true;

	m_isEnemyBullet = isEnemyBullet;

	m_startTime = m_clock.getElapsedTime();

	m_sprite.setPosition(m_pos);
	m_sprite.setRadius(3.0f);
	if (m_isEnemyBullet)
	{
		m_sprite.setFillColor(sf::Color::Red);
	}
	else
	{
		m_sprite.setFillColor(sf::Color::White);
	}
}


TrackingBullet::~TrackingBullet()
{
}

void TrackingBullet::update(sf::Vector2f target)
{
	m_vel = Normalize(m_pos - target); //Sets the velocity to a unit vector in the direction of the target
	m_pos += m_vel;
	m_sprite.setPosition(m_pos);
	if (m_clock.getElapsedTime() - m_startTime > lifeSpan
		&& m_alive == true) // If the bullet has exeeded the lifespan
	{
		m_alive = false; //The bullet is no longet alive
	}
}

sf::Vector2f TrackingBullet::Normalize(sf::Vector2f vec)
{
	float length = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	return sf::Vector2f(vec.x / length, vec.y / length);
}
