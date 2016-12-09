#pragma once

#include "stdafx.h"

class EventListener {
public:
	virtual void onEvent(sf::Event) = 0;
};