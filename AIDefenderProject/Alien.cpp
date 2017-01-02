#include "Alien.h"

Alien::Alien(sf::Vector2f pos, float speed) : m_position(pos), SPEED(speed) {
}

void Alien::render(sf::RenderWindow * window, Camera * camera) {
	sf::RectangleShape temp = m_sprite;
	temp.setPosition((*camera) + temp.getPosition());
	window->draw(temp);
}
