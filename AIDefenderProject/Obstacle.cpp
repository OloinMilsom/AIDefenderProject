#include "Obstacle.h"



Obstacle::Obstacle()
{
	srand(time(NULL));
	m_pos = sf::Vector2f(sf::Vector2f(rand() % (800 * 9), rand() % 600));
	m_vel = sf::Vector2f(1, 1);
	m_tex.loadFromFile("Resources/Meteor.png");
	m_sprite = sf::Sprite(m_tex, sf::IntRect(0, 0, m_tex.getSize().x, m_tex.getSize().y));
	m_sprite.setOrigin(m_tex.getSize().x / 2, m_tex.getSize().y / 2);
}


Obstacle::~Obstacle()
{
}

void Obstacle::update()
{
	m_pos += m_vel;
	m_sprite.setPosition(m_pos);
	if (m_pos.y > 650)
	{
		reset();
	}
}

void Obstacle::reset()
{
	m_pos = sf::Vector2f(sf::Vector2f(rand() % (800 * 9), -100));
}

void Obstacle::render(sf::RenderWindow * window, Camera * camera)
{
	m_sprite.setTexture(m_tex);
	window->draw((*camera) + m_sprite);
}

sf::Sprite Obstacle::getSprite()
{
	return m_sprite;
}
