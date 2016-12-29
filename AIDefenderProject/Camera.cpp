#include "Camera.h"

Camera::Camera(int width, int height)
	:m_screenCentre(width / 2, height / 2),
	 m_screenSize(width, height) {
}

void Camera::update(sf::Vector2f centre) {
	m_transform.x = m_oldCentre.x - centre.x;
	m_oldCentre = centre;
}

sf::Vector2f Camera::operator+(sf::Vector2f vec) {
	sf::Vector2f temp = m_transform + vec;
	while (temp.x > m_screenSize.x) {
		temp.x -= m_screenSize.x;
	}
	while (temp.x < 0) {
		temp.x += m_screenSize.x;
	}
	return temp;
}

sf::Sprite Camera::operator+(sf::Sprite spr) {
	spr.setPosition(m_transform + spr.getPosition());
	return spr;
}
