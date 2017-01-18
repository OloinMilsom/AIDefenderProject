#include "MiniMap.h"



MiniMap::MiniMap(std::deque<Alien *>* aliens, std::vector<Astronaut>* astronauts, Player * player)
{
	m_aliens = aliens;
	m_astronauts = astronauts;
	m_player = player;
	m_background = sf::RectangleShape();
	m_background.setFillColor(sf::Color(150, 150, 150, 100));
}


MiniMap::~MiniMap()
{
}

void MiniMap::render(sf::RenderWindow * window, int nestCount, int abductorCount, int mutantCount)
{
	m_background.setSize(sf::Vector2f(window->getSize().x, 80));
	window->draw(m_background);


	sf::RectangleShape temp;
	temp.setSize(sf::Vector2f(2.0f, 2.0f));

	
	temp.setFillColor(sf::Color::Magenta); //colour for nests
	for (int i = 0; i < nestCount; i++) //nests
	{
		if (m_aliens->at(i) ->getAlive())
		{
			temp.setPosition(m_aliens->at(i)->getPos().x / 9, m_aliens->at(i)->getPos().y / 9);

			window->draw(temp);
		}
	}
	
	temp.setFillColor(sf::Color::Yellow); //Colour for abductors
	for (int i = nestCount+1; i < nestCount+abductorCount; i++) //abductors
	{
		if (m_aliens->at(i)->getAlive())
		{
			temp.setPosition(m_aliens->at(i)->getPos().x / 9, m_aliens->at(i)->getPos().y / 9);

			window->draw(temp);
		}
	}
	
	temp.setFillColor(sf::Color::Red); //Colour for mutants
	for (int i = nestCount + abductorCount + 1; i <  m_aliens->size(); i++) //mutants
	{
		if (m_aliens->at(i)->getAlive())
		{
			temp.setPosition(m_aliens->at(i)->getPos().x / 9, m_aliens->at(i)->getPos().y / 9);

			window->draw(temp);
		}
	}

	
	temp.setFillColor(sf::Color::Green); //Colour for astronauts
	for (int i = 0; i < m_astronauts->size(); i++)
	{
		temp.setPosition(m_astronauts->at(i).getPos().x/9, m_astronauts->at(i).getPos().y/9);

		window->draw(temp);
	}

	temp.setFillColor(sf::Color::White);
	temp.setSize(sf::Vector2f(4.0f, 4.0f));
	temp.setPosition(m_player->getPosition().x / 9, m_player->getPosition().y / 9);
	window->draw(temp);
}
