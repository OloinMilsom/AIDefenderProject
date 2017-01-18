#include "CollisionManager.h"

CollisionManager::CollisionManager()
{

}

CollisionManager::CollisionManager(std::deque<Alien *>* aliens, std::vector<Astronaut> * astronauts, Player * player, std::vector<Powerup> * powerups, Camera * camera)
{
	m_aliens = aliens;
	m_astronauts = astronauts;
	m_player = player;
	m_bullets = BulletManager::getInstance()->getBulletPointer();
	m_missiles = BulletManager::getInstance()->getMissilePointer();
	m_powerups = powerups;
	m_camera = camera;
}


CollisionManager::~CollisionManager()
{
}

void CollisionManager::update()
{
	for (int i = 0; i < m_bullets->size(); i++) //Bullet Collisions
	{
		if (m_bullets->at(i).getAlive())
		{
			if (m_bullets->at(i).getIsEnemyBullet()) //Collisions for enemy bullets
			{
				if (Collide(m_player->getSprite(), m_bullets->at(i).getSprite()))
				{
					//Player hit by bullet
					m_player->hit();
					break;
				}
			}
			else //collisions for player bullets
			{
				for (int j = 0; j < m_aliens->size(); j++)
				{
					if (Collide(m_aliens->at(j)->getSprite(), m_bullets->at(i).getSprite()) && m_aliens->at(j)->getAlive())
					{
						m_aliens->at(j)->hit();
						m_bullets->at(i).hit();
						break;
					}
				}
			}
		}	
	}

	for (int i = 0; i < m_missiles->size(); i++) //Tracking bullet collisions
	{
		if (m_missiles->at(i).getAlive())
		{
			if (Collide(m_player->getSprite(), m_missiles->at(i).getSprite()))
			{
				//Player hit by missile
				break;
			}
		}
	}

	for (int i = 0; i < m_aliens->size(); i++)
	{
		if (m_aliens->at(i)->getAlive())
		{
			if (Collide(m_player->getSprite(), m_aliens->at(i)->getSprite()))
			{
				m_player->hit();
				m_aliens->at(i)->hit();
			}
		}
	}


	for (int i = 0; i < m_powerups->size(); i++) //Collision for powerups
	{
		if (Collide(m_player->getSprite(), m_powerups->at(i).getSprite()))
		{
			//Player picked up powerup
			m_player->giveHyperJump();
			m_powerups->at(i).trigger();
		}
	}
}

bool CollisionManager::Collide(sf::Sprite s1, sf::Sprite s2)
{
	sf::Sprite temp1 = (*m_camera) + s1;
	sf::Sprite temp2 = (*m_camera) + s2;
	return temp1.getGlobalBounds().intersects(temp2.getGlobalBounds());
}
