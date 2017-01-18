#pragma once
#include "Bullet.h"
#include "TrackingBullet.h"

//! BulletManager class
/*!
In charge of the creation, deletion and management of bullets in the game
*/
class BulletManager
{
private:
	std::vector<Bullet> m_bullets;
	static BulletManager *m_instance;
	
public:
	static BulletManager *getInstance() //!< singlton accessor
	{
		if (!m_instance)
		{
			m_instance = new BulletManager();
		}
		return m_instance;
	}


	BulletManager() {}; //!< BulletManager constructor
	~BulletManager(); //!< BulletManager destructor

	//! creates and adds a basic Bullet
	/*!
	\param pos position of the new Bullet
	\param vel velocity of the new Bullet
	\param isEnemyBullet flag for whether this is a player or enemy bullet
	*/
	void addBullet(sf::Vector2f pos, sf::Vector2f vel, bool isEnemyBullet);

	//! creates and adds a TrackingBullet
	/*!
	\param pos position of the new Bullet
	\param vel velocity of the new Bullet
	\param target vector to move towards
	*/
	void addTrackingBullet(sf::Vector2f pos, sf::Vector2f vel, const sf::Vector2f * target);

	void update(); //!< updates all bullets
	void smartBomb(); //!< creates and adds a smart bomb
	bool checkCollision(int, sf::Sprite); //!< checks collision between a sprite and a bullet

	//! BulletManager render function
	/*!
	\param window SFML window to render to
	\param camera adjusts positions based on the camera position
	draws all bullets to the screen
	*/
	void render(sf::RenderWindow * window, Camera * camera);

	bool getIsEnemyBullet(int index); //!< gets if bullet at index is an enemy bullet
	int getSize(); //!< gets size of the bullet container
};

