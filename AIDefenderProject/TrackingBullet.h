#pragma once
#include "Bullet.h"
class TrackingBullet: public Bullet
{
private:
	sf::Time lifeSpan = sf::seconds(10.0f); //The lifespan of a tracking bullet
public:
	TrackingBullet(sf::Vector2f, sf::Vector2f);
	~TrackingBullet();
	void reset(sf::Vector2f, sf::Vector2f);
	void update(sf::Vector2f pos);
	sf::Vector2f Normalize(sf::Vector2f);
};

