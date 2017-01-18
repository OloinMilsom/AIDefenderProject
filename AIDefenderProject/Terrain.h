#pragma once
#include "stdafx.h"
#include <random>
#include <vector>
#include "Camera.h"

//! Terrain class
/*!
Terrain class represents the generated floor terrain in the game. Terrain is
generated to appear like a harsh martian surface
*/
class Terrain {
private:
	std::vector<sf::Vertex> m_vertices;
	int m_width;
	int m_height;
public:
	Terrain(int width = 0, int height = 0, int deviation = 0); //!< Terrain constructor
	void update(); //!< Terrain update function

	//! Terrain render function
	/*!
	\param window SFML window to render to
	\param camera adjusts positions based on the camera position
	draws the terrain to the screen
	*/
	void render(sf::RenderWindow * window, Camera * camera);

	float getMTV(sf::Vector2f) const; //!< get the minimum height needed to remove a position from below the terrain
	float getHeightAt(float x) const; //!< get the height value along the terrain for a given x value
};