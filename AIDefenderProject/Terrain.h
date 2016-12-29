#pragma once
#include "stdafx.h"
#include <random>
#include <vector>
#include "Camera.h"

class Terrain {
private:
	std::vector<sf::Vertex> m_vertices;
public:
	Terrain(int width = 0, int height = 0, int deviation = 0);
	void update(Camera camera);
	void render(sf::RenderWindow * window);
	float underneath(sf::Vector2f);
};