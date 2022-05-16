#pragma once

#include <vector>
#include "Button.h"
#include "SFML/Graphics.hpp"

class Window;

class MenuScreen
{
public:
	MenuScreen(Window* window);
	void Menu();

private:
	void createButton();
	void draw();

	Window* m_window;
	std::vector<Button> m_buttons;
};