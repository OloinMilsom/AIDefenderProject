#pragma once

#include "stdafx.h"

//! EventListener base class
/*!
Base class for any class that needs to listen to keyboard events
*/
class EventListener {
public:
	virtual void onEvent(sf::Event) = 0; //!< pure virtual function for event response in EventListeners
};