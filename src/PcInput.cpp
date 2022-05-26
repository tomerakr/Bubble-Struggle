#include "PcInput.h"

std::pair<sf::Vector2f, bool> PcInput::getInput(std::vector<sf::Keyboard::Key> keys)
{
	return std::make_pair(readDirection(keys), readShoot(keys));
}

sf::Vector2f PcInput::readDirection(std::vector<sf::Keyboard::Key> keys)
{
	auto direction = sf::Vector2f();

	if (sf::Keyboard::isKeyPressed(keys[static_cast<int>(Keys::Left)]))
	{
		direction = sf::Vector2f(-1, 0);
	}
	else if (sf::Keyboard::isKeyPressed(keys[static_cast<int>(Keys::Right)]))
	{
		direction = sf::Vector2f(1, 0);
	}
	else
	{
		direction = sf::Vector2f(0, 0);
	}

	return direction;
}

bool PcInput::readShoot(std::vector<sf::Keyboard::Key> keys)
{
	return sf::Keyboard::isKeyPressed(keys[static_cast<int>(Keys::Shoot)]);
}
 