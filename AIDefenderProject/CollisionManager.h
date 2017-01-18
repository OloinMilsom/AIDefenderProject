#pragma once
#include "stdafx.h"
#include <deque>
#include "Alien.h"
#include "Astronaut.h"
#include "Player.h"
#include "BulletManager.h"
#include "PowerupManager.h"
#include "Camera.h"

class CollisionManager
{
private:
	std::deque<Alien *> * m_aliens;	
	std::vector<Astronaut> * m_astronauts;
	Player * m_player;
	std::vector<Bullet> * m_bullets;
	std::vector<TrackingBullet> * m_missiles;
	std::vector<Powerup>* m_powerups;
	Camera * m_camera;

public:
	CollisionManager();
	CollisionManager(std::deque<Alien *>*, std::vector<Astronaut> *, Player *, std::vector<Powerup>*, Camera *);
	~CollisionManager();

	void update();

	bool Collide(sf::Sprite, sf::Sprite);
};

