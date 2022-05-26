#pragma once

#include "Macros.h"
#include "SFML/Graphics.hpp"

class Resources;
class Window;

class LevelCreator
{
public:
	LevelCreator() = default;
	void createLevel(Window* window);
	void clear();
	void save();

private:
	void draw();
};