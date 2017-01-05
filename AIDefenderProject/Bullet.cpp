#include "Bullet.h"



Bullet::Bullet(sf::Vector2f pos, sf::Vector2f vel, bool isEnemyBullet)
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


Bullet::~Bullet()
{
}

void Bullet::reset(sf::Vector2f pos, sf::Vector2f vel, bool isEnemyBullet) //Mignt not be needed if the manager has an array of "new" bullets that are deleted
{
	m_pos = pos;
	m_vel = vel;

	m_alive = true;

	m_isEnemyBullet = isEnemyBullet;

	m_startTime = m_clock.getElapsedTime();

	m_sprite.setPosition(m_pos);

	if (m_isEnemyBullet)
	{
		m_sprite.setFillColor(sf::Color::Red);
	}
	else
	{
		m_sprite.setFillColor(sf::Color::White);
	}
}

void Bullet::render(sf::RenderWindow * window, Camera * camera)
{
	if (m_alive)
	{
		sf::CircleShape temp = m_sprite;
		temp.setPosition((*camera) + temp.getPosition());
		window->draw(temp);
	}
}

void Bullet::update()
{
	m_pos += m_vel;
	m_sprite.setPosition(m_pos);
	if (m_clock.getElapsedTime() - m_startTime > lifeSpan
		&& m_alive == true) // If the bullet has exeeded the lifespan
	{
		m_alive = false; //The bullet is no longet alive
	}
}

sf::Vector2f Bullet::Normalize(sf::Vector2f vec)
{
	float length = sqrt((vec.x * vec.x) + (vec.y * vec.y));

	return sf::Vector2f(vec.x / length, vec.y / length);
}

bool Bullet::getAlive() { return m_alive; }
bool Bullet::getIsEnemyBullet() { return m_isEnemyBullet; }
sf::Vector2f Bullet::getPos() { return m_pos; }
