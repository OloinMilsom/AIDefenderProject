#include "Powerup.h"



Powerup::Powerup(int type)
{
	m_type = type;
	srand(time(NULL));
	m_alive = true;

	m_tex.loadFromFile("Resources/PickUp.png");
	m_sprite = sf::Sprite(m_tex, sf::IntRect(0, 0, m_tex.getSize().x, m_tex.getSize().y));
	m_sprite.setOrigin(m_tex.getSize().x / 2, m_tex.getSize().y / 2);
	m_sprite.setPosition(sf::Vector2f(rand() % (800 * 9), rand() % 600));
}

void Powerup::reset(int type)
{
	m_type = type;
	m_sprite.setPosition(sf::Vector2f(rand() % (800 * 9), rand() % 600));
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
		m_sprite.setTexture(m_tex);
		window->draw((*camera) + m_sprite);
	}
}

bool Powerup::getAlive(){ return m_alive; }

int Powerup::getType()
{
	return m_type;
}

sf::Sprite Powerup::getSprite()
{
	return m_sprite;
}



