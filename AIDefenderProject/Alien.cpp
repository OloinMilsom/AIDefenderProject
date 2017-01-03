#include "Alien.h"

Alien::Alien(sf::Vector2f pos, float speed, float acceleration) : m_position(pos), MAX_SPEED(speed), MAX_ACCELERATION(acceleration) {
}

void Alien::render(sf::RenderWindow * window, Camera * camera) {
	sf::RectangleShape temp = m_sprite;
	temp.setPosition((*camera) + temp.getPosition());

	sf::VertexArray velAccel(sf::Lines, 4);
	velAccel[0].position = (*camera) + m_position;
	velAccel[0].color = sf::Color::Blue;
	velAccel[1].position = (*camera) + m_position + m_velocity;
	velAccel[1].color = sf::Color::Blue;	
	velAccel[2].position = (*camera) + m_position;
	velAccel[2].color = sf::Color::Green;
	velAccel[3].position = (*camera) + m_position + m_acceleration;
	velAccel[3].color = sf::Color::Green;
	window->draw(temp);
	window->draw(velAccel);
}
