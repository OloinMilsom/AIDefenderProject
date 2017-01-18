#pragma once
#include "stdafx.h"
#include <deque>
#include "Alien.h"
#include "Astronaut.h"
#include "Player.h"

class Alien;
class Astronaut;

//! MiniMap class
/*!
Draws a small version of the gameworld showing data beyond the edge of the screen
*/
class MiniMap
{
private:
	sf::RectangleShape m_background;
	const std::deque<Alien *> * m_aliens;
	const std::vector<Astronaut> * m_astronauts;
	const Player * m_player;
public:
	MiniMap(std::deque<Alien *> *, std::vector<Astronaut> *, Player *); //!< MiniMap constructor taking types to draw
	~MiniMap(); //!< MiniMap destructor

	//! MiniMap render function
	/*!
	\param window SFML window to render to
	draws the MiniMap to the screen
	*/
	void render(sf::RenderWindow * window, int, int, int);
};

