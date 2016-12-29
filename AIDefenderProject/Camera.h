#pragma once
#include "stdafx.h"

class Camera {
private:
	sf::Vector2f m_transform;
	sf::Vector2f m_screenCentre;
	sf::Vector2f m_screenSize;
	sf::Vector2f m_oldCentre;
public:
	Camera(int width = 0, int height = 0);
	void update(sf::Vector2f centre);
	sf::Vector2f operator+(sf::Vector2f vec);
	sf::Sprite operator+(sf::Sprite spr);
};