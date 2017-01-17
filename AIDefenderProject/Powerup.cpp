#include "Powerup.h"



Powerup::Powerup(int type)
{
	m_type = type;
	srand(time(NULL));
	m_pos = sf::Vector2f(0, 0);
	m_alive = true;
}

void Powerup::reset(int type)
{
	m_type = type;
	srand(time(NULL));
	m_pos = sf::Vector2f(0, 0);
	m_alive = true;
}

void Powerup::trigger()
{
	m_alive = false;
}

Powerup::~Powerup()
{
}

void Powerup::render(sf::RenderWindow * window, Camera * camera)
{
	if (m_alive)
	{
		sf::CircleShape temp = m_sprite;
		temp.setPosition((*camera) + temp.getPosition());
		window->draw(temp);
	}
}

bool Powerup::getAlive(){ return m_alive; }

int Powerup::getType()
{
	return m_type;
}

sf::CircleShape Powerup::getRect()
{
	return m_sprite;
}



