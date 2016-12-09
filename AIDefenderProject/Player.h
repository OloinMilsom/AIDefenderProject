#pragma once
#include "stdafx.h"
#include "EventListener.h"

class Player : EventListener {
private:
	sf::Vector2f pos;
public:
	Player();
	void onEvent(sf::Event evt);
};