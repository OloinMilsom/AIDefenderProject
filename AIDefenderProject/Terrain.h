#pragma once
#include "stdafx.h"
#include <random>
#include <vector>
#include "Camera.h"

class Terrain {
private:
	std::vector<sf::Vertex> m_vertices;
	int m_width;
	int m_height;
public:
	Terrain(int width = 0, int height = 0, int deviation = 0);
	void update();
	void render(sf::RenderWindow * window, Camera * camera);
	float getMTV(sf::Vector2f) const;
	float getHeightAt(float x) const;
};