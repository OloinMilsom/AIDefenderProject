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
#include "ObstacleManager.h"
#include "CollisionManager.h"

//! Class manages game logic
/*!
	This class includes all the game logic and is the controller class for
	the project. It contains all the game entities and manages communication
	between them.
*/
class Game : EventListener {
private:
	sf::RenderWindow * m_window;
	InputManager m_inputManager;

	Player * m_player;
	Terrain m_terrain;
	std::vector<Astronaut> m_astronauts;
	AlienManager * m_alienManager;
	PowerupManager m_powerupManager;
	CollisionManager m_collisionManager;
	ObstacleManager m_obsticleManager;
	
	Camera m_camera;
	sf::Clock m_clock;
	float m_lastFrameTime;

	void update(float dt);
	void render();

public:
	Game(); //!< Game constructor
	void loop(); //!< Game loop, all run time game logic executed here
	void onEvent(sf::Event evt); //!< Game responds to key events here
};