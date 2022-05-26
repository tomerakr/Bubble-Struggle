#include "LevelCreator.h"
#include "WIndow.h"
#include "Resources.h"

void LevelCreator::createLevel(Window* window)
{
	if (sf::Event event; window->getWindow().pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			window->close();

		default:
			break;
		}
	}

	draw();
}

void LevelCreator::draw()
{

}