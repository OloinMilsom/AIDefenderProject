#pragma once
//////////////////////////////////////////////////////////// 
// Headers 
//////////////////////////////////////////////////////////// 
#include "stdafx.h" 
#ifdef _DEBUG 
#pragma comment(lib,"sfml-graphics-d.lib") 
#pragma comment(lib,"sfml-audio-d.lib") 
#pragma comment(lib,"sfml-system-d.lib") 
#pragma comment(lib,"sfml-window-d.lib") 
#pragma comment(lib,"sfml-network-d.lib") 
#else 
#pragma comment(lib,"sfml-graphics.lib") 
#pragma comment(lib,"sfml-audio.lib") 
#pragma comment(lib,"sfml-system.lib") 
#pragma comment(lib,"sfml-window.lib") 
#pragma comment(lib,"sfml-network.lib") 
#endif 
#pragma comment(lib,"opengl32.lib") 
#pragma comment(lib,"glu32.lib") 

#include "SFML/Graphics.hpp" 
#include "SFML/OpenGL.hpp" 
#include <iostream> 
#define _USE_MATH_DEFINES
#include <math.h>

#include "InputManager.h"
#include "Player.h"
#include "Terrain.h"
#include "BulletManager.h"
#include "Camera.h"
#include "Astronaut.h"
#include "AlienManager.h"
#include "PowerupManager.h"

class Game : EventListener {
private:
	sf::RenderWindow * m_window;
	InputManager m_inputManager;
	//BulletManager m_bulletManager;

	Player * m_player;
	Terrain m_terrain;
	std::vector<Astronaut> m_astronauts;
	AlienManager * m_alienManager;
	
	Camera m_camera;
	sf::Clock m_clock;
	float m_lastFrameTime;

	void update(float dt);
	void render();

public:
	Game();
	void loop();
	void onEvent(sf::Event evt);
};