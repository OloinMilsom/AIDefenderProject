#include "Camera.h"

Camera::Camera(int screenWidth, int screenHeight, int worldWidth, int worldHeight)
	:m_screenCentre(screenWidth / 2, screenHeight / 2),
	 m_worldSize(worldWidth, worldHeight) {
}

void Camera::update(sf::Vector2f centre) {
	m_transform.x = m_screenCentre.x - centre.x;
}

sf::Vector2f Camera::operator+(sf::Vector2f vec) {
	sf::Vector2f temp = m_transform + vec;
	while (temp.x > m_worldSize.x) {
		temp.x -= m_worldSize.x;
	}
	while (temp.x < 0) {
		temp.x += m_worldSize.x;
	}
	return temp;
}

sf::Sprite Camera::operator+(sf::Sprite spr) {
	spr.setPosition(m_transform + spr.getPosition());
	return spr;
}
