#include "BulletManager.h"



BulletManager::BulletManager()
{
}


BulletManager::~BulletManager()
{
}

void BulletManager::AddBullet(sf::Vector2f pos, sf::Vector2f vel, bool isEnemyBullet)
{
	bool needNewBullet = true; //Temorary bool to check if a new bullet is needed

	for (int i = 0; i < m_bullets.size(); i++) //for the size of the bullet vector
	{
		if (!m_bullets.at(i).getAlive())
		{
			m_bullets.at(i).Reset(pos, vel, isEnemyBullet);
			needNewBullet = false; //Don't need a new bullet
			break; //loop is no longer needed
		}
	}

	if (needNewBullet)
	{
		m_bullets.push_back(Bullet(pos, vel, isEnemyBullet)); //Adds a bullet to the vector
	}
	
}

void BulletManager::Update()
{
	for (int i = 0; i < m_bullets.size(); i++) //for the size of the bullet array
	{
		if (m_bullets.at(i).getAlive()) //Only render if the bullet is alive
		{
			m_bullets.at(i).Update(); //Update the bullet
		}
	}
}

void BulletManager::render(sf::RenderWindow * window)
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets.at(i).render(window);
	}
}

bool BulletManager::CheckCollision(int index, sf::RectangleShape rect) 
{
	return rect.getGlobalBounds().contains(m_bullets.at(index).getPos()); //Takes the rect from the player or enemy's rectangle shape and checks if it contains the bullet
}

bool BulletManager::getIsEnemyBullet(int index) { return m_bullets.at(index).getIsEnemyBullet(); }