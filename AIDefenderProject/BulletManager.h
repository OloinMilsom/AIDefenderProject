#pragma once
#include "Bullet.h"
#include "TrackingBullet.h"
class BulletManager
{
private:
	std::vector<Bullet> m_bullets;
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

	void addBullet(sf::Vector2f, sf::Vector2f, bool, bool);
	void update();
	bool checkCollision(int, sf::RectangleShape);
	void render(sf::RenderWindow * window, Camera * camera);

	bool getIsEnemyBullet(int index);
	int getSize();
};

