#pragma once

#include "Bear.h"
#include "Window.h"

class Controller
{
public:
	Controller();
	void play();
	void restartLevel();
	
private:
	Bear m_bear;
	Window m_window;
};

