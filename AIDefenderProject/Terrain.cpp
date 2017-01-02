#include "Terrain.h"


Terrain::Terrain(int width, int height, int deviation) : m_width(width) {
	m_height = std::numeric_limits<int>::max();
	int noOfPoints = width / 10;
	int originalHeight = height;
	std::default_random_engine rnd(std::time(0));
	if (deviation != 0) {
		std::normal_distribution<float> normal(0, deviation);

		for (int i = 0; i < noOfPoints; i++) {
			if (height < m_height) {
				m_height = height;
			}
			m_vertices.push_back(sf::Vertex(sf::Vector2f(i * 10, height), sf::Color(204, 119, 34)));
			height += normal(rnd);
			height += (originalHeight - height) / deviation;
		}
		m_vertices.push_back(sf::Vertex(sf::Vector2f(width, originalHeight), sf::Color(204, 119, 34)));
	}
}

void Terrain::update() {
	/*for (int i = 0; i < m_vertices.size(); i++) {
		m_vertices[i].position = camera + m_vertices[i].position;
	}
	auto comp = [](sf::Vertex v1, sf::Vertex v2) {
		return v1.position.x < v2.position.x;
	};
	std::sort(m_vertices.begin(), m_vertices.end(), comp);*/
}

void Terrain::render(sf::RenderWindow * window, Camera * camera) {
	sf::VertexArray temp = sf::VertexArray(sf::Lines, m_vertices.size() * 2);
	for (int i = 0; i < m_vertices.size() - 1; i++) {
		temp[2 * i] = m_vertices[i];
		temp[2 * i].position = (*camera) + temp[2 * i].position;
		temp[2 * i + 1] = m_vertices[i+1];
		temp[2 * i + 1].position = (*camera) + temp[2 * i + 1].position;
		if (temp[2 * i].position.x > temp[2 * i + 1].position.x) {
			temp[2 * i + 1].position.x += m_width;
		}
	}
	window->draw(temp);
}

float Terrain::getMTV(sf::Vector2f pos) {
	if (pos.y > m_height) {
		float y = getHeightAt(pos.x);
		if (y < pos.y) {
			return y - pos.y;
		}
		else return 0;
	}
	return 0;
}

float Terrain::getHeightAt(float x)
{
	if (!m_vertices.empty()) {
		while (x > m_width) {
			x -= m_width;
		}
		while (x < 0) {
			x += m_width;
		}
		for (int i = 0; i < m_vertices.size() - 1; i++) {
			if (x < m_vertices[i + 1].position.x) {
				// lerp
				return m_vertices[i].position.y + (x - m_vertices[i].position.x) * ((m_vertices[i + 1].position.y - m_vertices[i].position.y) / (m_vertices[i + 1].position.x - m_vertices[i].position.x));
			}
		}
	}
}
