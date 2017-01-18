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

	void addBullet(sf::Vector2f, sf::Vector2f, bool);
	void addTrackingBullet(sf::Vector2f, sf::Vector2f, const sf::Vector2f * target);
	void update();
	void smartBomb();
	bool checkCollision(int, sf::Sprite);
	void render(sf::RenderWindow * window, Camera * camera);

	bool getIsEnemyBullet(int index);
	int getSize();
};

