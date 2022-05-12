#pragma once

#include "Macros.h"

class Resources;

class LevelCreator
{
public:
	LevelCreator();
	void createLevel(sf::RenderWindow& window);
	void clear();
	void save();
};