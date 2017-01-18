#include "Powerup.h"



Powerup::Powerup(int type)
{
	m_type = type;
	srand(time(NULL));
	m_sprite = sf::CircleShape(10);
	m_sprite.setPosition(sf::Vector2f(rand() % (800 * 9), rand() % 600));
	m_alive = true;
	
	if (type == 0)
	{
		m_sprite.setFillColor(sf::Color::Yellow);
	}
	else
	{
		m_sprite.setFillColor(sf::Color::Blue);
	}
}

void Powerup::reset(int type)
{
	m_type = type;
	m_sprite.setPosition(sf::Vector2f(rand() % (800 * 9), rand() % 600));
	m_alive = true;

	if (type == 0)
	{
		m_sprite.setFillColor(sf::Color::Yellow);
	}
	else
	{
		m_sprite.setFillColor(sf::Color::Blue);
	}
}

void Powerup::trigger()
{
	//m_alive = false;
	m_sprite.setFillColor(sf::Color::White);
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



