#pragma once
#include "Bullet.h"
class TrackingBullet: public Bullet
{
public:
	TrackingBullet(sf::Vector2f, sf::Vector2f, bool);
	~TrackingBullet();
	void update(sf::Vector2f);
	sf::Vector2f Normalize(sf::Vector2f);
};

