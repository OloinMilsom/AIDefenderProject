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
	const sf::Vector2f * m_target;
public:
	TrackingBullet(sf::Vector2f, sf::Vector2f, const sf::Vector2f * target); //!< tracking bullet constructor
	~TrackingBullet(); //<! tracking bullet destructor
	void update(); //<! updates a tracking bullet
	sf::Vector2f Normalize(sf::Vector2f); //!< Vector normalise helper
};

