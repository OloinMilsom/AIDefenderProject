#pragma once
#include "Bullet.h"

//! TrackingBullet class
/*!
Like Bullet only the TrackingBullet follows a given position
*/
class TrackingBullet: public Bullet
{
private:
	sf::Time lifeSpan = sf::seconds(10.0f); //The lifespan of a tracking bullet
public:
	TrackingBullet(sf::Vector2f, sf::Vector2f); //!< tracking bullet constructor
	~TrackingBullet(); //<! tracking bullet destructor
	void reset(sf::Vector2f, sf::Vector2f);
	void update(sf::Vector2f pos); //<! updates a tracking bullet
	sf::Vector2f Normalize(sf::Vector2f); //!< Vector normalise helper
};

