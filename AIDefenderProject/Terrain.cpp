#include "Terrain.h"


Terrain::Terrain(int width, int height, int deviation) {
	int noOfPoints = width / 10;
	int originalHeight = height;
	std::default_random_engine rnd(std::time(0));
	if (deviation != 0) {
		std::normal_distribution<float> normal(0, deviation);

		m_vertices = sf::VertexArray(sf::LineStrip, noOfPoints + 1);
		for (int i = 0; i < noOfPoints; i++) {
			m_vertices[i] = sf::Vector2f(i * 10, height);
			m_vertices[i].color = sf::Color(204,119,34);
			height += normal(rnd);
			height += (originalHeight - height) / deviation;
		}
		// temp line to check difference
		m_vertices[noOfPoints] = sf::Vector2f(width, originalHeight);
		m_vertices[noOfPoints].color = sf::Color::Green;
	}
}

void Terrain::render(sf::RenderWindow * window) {
	window->draw(m_vertices);
}

float Terrain::underneath(sf::Vector2f pos) {
	for (int i = 0; i < m_vertices.getVertexCount() - 1; i++) {
		if (pos.x < m_vertices[i + 1].position.x) {
			// lerp
			float y = m_vertices[i].position.y + (pos.x - m_vertices[i].position.x) * ((m_vertices[i + 1].position.y - m_vertices[i].position.y) / (m_vertices[i + 1].position.x - m_vertices[i].position.x));
			if (y < pos.y) {
				return y - pos.y;
			}
			else return 0;
		}
	}
	return 0;
}
