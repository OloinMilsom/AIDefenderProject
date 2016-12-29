#include "Terrain.h"


Terrain::Terrain(int width, int height, int deviation) {
	int noOfPoints = width / 10;
	int originalHeight = height;
	std::default_random_engine rnd(std::time(0));
	if (deviation != 0) {
		std::normal_distribution<float> normal(0, deviation);

		for (int i = 0; i < noOfPoints; i++) {
			m_vertices.push_back(sf::Vertex(sf::Vector2f(i * 10, height), sf::Color(204, 119, 34)));
			height += normal(rnd);
			height += (originalHeight - height) / deviation;
		}
	}
}

void Terrain::update(Camera camera) {
	for (int i = 0; i < m_vertices.size(); i++) {
		m_vertices[i].position = camera + m_vertices[i].position;
	}
	auto comp = [](sf::Vertex v1, sf::Vertex v2) {
		return v1.position.x < v2.position.x;
	};
	std::sort(m_vertices.begin(), m_vertices.end(), comp);
}

void Terrain::render(sf::RenderWindow * window) {	
	sf::VertexArray temp = sf::VertexArray(sf::LineStrip, m_vertices.size());
	for (int i = 0; i < m_vertices.size(); i++) {
		temp[i] = m_vertices[i];
	}
	window->draw(temp);
}

float Terrain::underneath(sf::Vector2f pos) {
	if (!m_vertices.empty()) {
		for (int i = 0; i < m_vertices.size() - 1; i++) {
			if (pos.x < m_vertices[i + 1].position.x) {
				// lerp
				float y = m_vertices[i].position.y + (pos.x - m_vertices[i].position.x) * ((m_vertices[i + 1].position.y - m_vertices[i].position.y) / (m_vertices[i + 1].position.x - m_vertices[i].position.x));
				if (y < pos.y) {
					return y - pos.y;
				}
				else return 0;
			}
		}
	}
	return 0;
}
