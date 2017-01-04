#pragma once
#include "stdafx.h"

class Camera {
private:
	sf::Vector2f m_transform;
	sf::Vector2f m_screenCentre;
	sf::Vector2f m_worldSize;
public:
	Camera(int screenWidth = 0, int screenHeight = 0, int worldWidth = 0, int worldHeight = 0);
	void update(sf::Vector2f centre);
	sf::Vector2f operator+(sf::Vector2f vec) const;
	sf::Sprite operator+(sf::Sprite spr);
};