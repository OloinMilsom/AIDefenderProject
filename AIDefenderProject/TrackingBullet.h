#pragma once
#include "Bullet.h"
class TrackingBullet: public Bullet
{
private:
	sf::Time lifeSpan = sf::seconds(10.0f); //The lifespan of a tracking bullet
	const sf::Vector2f * m_target;
public:
	TrackingBullet(sf::Vector2f, sf::Vector2f, const sf::Vector2f * target);
	~TrackingBullet();
	void update();
	sf::Vector2f Normalize(sf::Vector2f);
};

