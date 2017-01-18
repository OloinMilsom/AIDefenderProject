#include "BulletManager.h"

BulletManager *BulletManager::m_instance = 0;

//BulletManager::BulletManager()
//{
//}


BulletManager::~BulletManager()
{
}

void BulletManager::addBullet(sf::Vector2f pos, sf::Vector2f vel, bool isEnemyBullet)
{
	bool needNewBullet = true; //Temorary bool to check if a new bullet is needed

	for (int i = 0; i < m_bullets.size(); i++) //for the size of the bullet vector
	{
		if (!m_bullets.at(i).getAlive())
		{
			m_bullets.at(i).reset(pos, vel, isEnemyBullet);
			needNewBullet = false; //Don't need a new bullet
			break; //loop is no longer needed
		}
	}

	if (needNewBullet)
	{
			m_bullets.push_back(Bullet(pos, vel, isEnemyBullet)); //Adds a bullet to the vector
	}
}

void BulletManager::addTrackingBullet(sf::Vector2f pos, sf::Vector2f vel)
{
	bool needNewBullet = true; //Temorary bool to check if a new bullet is needed

	for (int i = 0; i < m_missiles.size(); i++) //for the size of the bullet vector
	{
		if (!m_missiles.at(i).getAlive())
		{
			m_missiles.at(i).reset(pos, vel);
			needNewBullet = false; //Don't need a new bullet
			break; //loop is no longer needed
		}
	}

	if (needNewBullet)
	{
		m_missiles.push_back(TrackingBullet(pos, vel)); //Adds a bullet to the vector
	}
}

void BulletManager::update(sf::Vector2f pos)
{
	for (int i = 0; i < m_bullets.size(); i++) //for the size of the bullet array
	{
		if (m_bullets.at(i).getAlive()) //Only render if the bullet is alive
		{
			m_bullets.at(i).update(); //Update the bullet
		}
	}
	for (int i = 0; i < m_missiles.size(); i++) //for the size of the bullet array
	{
		if (m_missiles.at(i).getAlive()) //Only render if the bullet is alive
		{
			m_missiles.at(i).update(pos); //Update the bullet
		}
	}
}

void BulletManager::render(sf::RenderWindow * window, Camera * camera)
{
	for (int i = 0; i < m_bullets.size(); i++)
	{
		m_bullets.at(i).render(window, camera);
	}
	for (int i = 0; i < m_missiles.size(); i++)
	{
		m_missiles.at(i).render(window, camera);
	}
}

bool BulletManager::getIsEnemyBullet(int index) { return m_bullets.at(index).getIsEnemyBullet(); }

int BulletManager::getMissileSize()
{
	return m_missiles.size();;
}

std::vector<Bullet>* BulletManager::getBulletPointer()
{
	return &m_bullets;
}

std::vector<TrackingBullet>* BulletManager::getMissilePointer()
{
	return &m_missiles;
}

int BulletManager::getBulletSize()
{
	return m_bullets.size();
}
