#pragma once
#include "stdafx.h" 


class Bullet
{
private:
	sf::Time lifeSpan = sf::seconds(4.0f); //The lifespan of a bullet

	sf::Vector2f m_pos; //Position of bullet
	sf::Vector2f m_vel; //Velocity of bullet

	sf::Clock m_clock; //Clock for getting current time
	sf::Time m_startTime; //Time that the bullet is created or reset

	sf::CircleShape m_sprite;

	bool m_alive; //Is the bulet currently active
	bool m_isEnemyBullet; //Does this bullet belong to an enemy
public:
	Bullet(sf::Vector2f, sf::Vector2f, bool);
	~Bullet();

	void Update();
	void render(sf::RenderWindow * window);
	void Reset(sf::Vector2f, sf::Vector2f, bool);

	bool getAlive();
	bool getIsEnemyBullet();
	sf::Vector2f getPos();
};

