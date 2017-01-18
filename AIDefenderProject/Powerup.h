#pragma once
#include "stdafx.h" 
#include "Camera.h"
class Powerup
{
protected:
	//sf::Vector2f m_pos; //Position of powerup
	sf::Texture m_tex;
	sf::Sprite m_sprite;
	bool m_alive; //Is the powerup currently active
	int m_type; //0 = hyperjump charge
public:
	Powerup(int);
	~Powerup();

	void render(sf::RenderWindow * window, Camera * camera);
	void reset(int);
	void trigger();
	bool getAlive();
	int getType();
	sf::Sprite getSprite();
};

