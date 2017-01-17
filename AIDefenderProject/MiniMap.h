#pragma once
#include "stdafx.h"
#include <deque>
#include "Alien.h"
#include "Astronaut.h"
#include "Player.h"

class Alien;
class Astronaut;

class MiniMap
{
private:
	sf::RectangleShape m_background;
	const std::deque<Alien *> * m_aliens;
	const std::vector<Astronaut> * m_astronauts;
	const Player * m_player;
public:
	MiniMap(std::deque<Alien *> *, std::vector<Astronaut> *, Player *);
	~MiniMap();

	void render(sf::RenderWindow * window, int, int, int);
};

