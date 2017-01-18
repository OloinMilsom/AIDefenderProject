#include "Bullet.h"



Bullet::Bullet(sf::Vector2f pos, sf::Vector2f vel, bool isEnemyBullet)
{
	m_pos = pos;
	m_vel = vel;

	m_tex.loadFromFile("Resources/Laser.png");
	m_sprite = sf::Sprite(m_tex, sf::IntRect(0, 0, m_tex.getSize().x / 2, m_tex.getSize().y));
	m_sprite.setOrigin(m_tex.getSize().x / 4, m_tex.getSize().y / 2);

	m_alive = true;

	m_isEnemyBullet = isEnemyBullet;

	m_startTime = m_clock.getElapsedTime();

	m_sprite.setPosition(m_pos);

	if (isEnemyBullet)
	{
		m_sprite.setColor(sf::Color::Red);
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

	if (isEnemyBullet)
	{
		m_sprite.setColor(sf::Color::Red);
	}
	else
	{
		m_sprite.setColor(sf::Color::White);
	}
	
}

void Bullet::hit()
{
	m_alive = false;
}

void Bullet::render(sf::RenderWindow * window, Camera * camera)
{
	if (m_alive)
	{
		sf::Sprite temp = m_sprite;
		temp.setPosition((*camera) + temp.getPosition());
		window->draw(temp);
	}
}

void Bullet::update()
{
	if (m_alive)
	{
		m_pos += m_vel;
		m_sprite.setPosition(m_pos);
		if (m_clock.getElapsedTime() - m_startTime > lifeSpan
			&& m_alive == true) // If the bullet has exeeded the lifespan
		{
			m_alive = false; //The bullet is no longet alive
		}
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

sf::Sprite Bullet::getSprite()
{
	return m_sprite;
}
