#pragma once
#include "stdafx.h"
#include "camera.h"
class Obstacle
{
private:
	sf::Vector2f m_pos;
	sf::Vector2f m_vel;
	sf::Texture m_tex;
	sf::Sprite m_sprite;
public:
	Obstacle();
	~Obstacle();

	void update();
	void reset();
	void render(sf::RenderWindow * window, Camera * camera);
	sf::Sprite getSprite();
};

