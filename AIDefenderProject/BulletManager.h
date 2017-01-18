#pragma once
#include "Bullet.h"
#include "TrackingBullet.h"
class BulletManager
{
private:
	std::vector<Bullet> m_bullets;
	std::vector<TrackingBullet> m_missiles;
	static BulletManager *m_instance;
	
public:
	static BulletManager *getInstance()
	{
		if (!m_instance)
		{
			m_instance = new BulletManager();
		}
		return m_instance;
	}


	BulletManager() {};
	~BulletManager();

	void addBullet(sf::Vector2f, sf::Vector2f, bool);
	void addTrackingBullet(sf::Vector2f, sf::Vector2f);
	void update(sf::Vector2f pos);
	void render(sf::RenderWindow * window, Camera * camera);

	bool getIsEnemyBullet(int index);
	int getBulletSize();
	int getMissileSize();
	std::vector<Bullet>* getBulletPointer();
	std::vector<TrackingBullet>* getMissilePointer();
};

