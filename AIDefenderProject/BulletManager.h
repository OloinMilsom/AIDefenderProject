#pragma once
#include "Bullet.h"
class BulletManager
{
private:
	std::vector<Bullet> m_bullets;
	
public:
	BulletManager();
	~BulletManager();

	void AddBullet(sf::Vector2f, sf::Vector2f, bool);
	void Update();
	bool CheckCollision(int, sf::RectangleShape);
	void render(sf::RenderWindow * window);

	bool getIsEnemyBullet(int index);
};

