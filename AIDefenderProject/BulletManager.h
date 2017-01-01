#pragma once
#include "Bullet.h"
class BulletManager
{
private:
	std::vector<Bullet> m_bullets;
	
public:
	BulletManager();
	~BulletManager();

	void addBullet(sf::Vector2f, sf::Vector2f, bool);
	void update();
	bool checkCollision(int, sf::RectangleShape);
	void render(sf::RenderWindow * window, Camera camera);

	bool getIsEnemyBullet(int index);
};

