#pragma once
#include "stdafx.h"
#include <random>

class Terrain {
private:
	sf::VertexArray m_vertices;
public:
	Terrain(int width = 0, int height = 0, int deviation = 0);
	void render(sf::RenderWindow * window);
	float underneath(sf::Vector2f);
};