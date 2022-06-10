#include "PcInput.h"

std::pair<sf::Vector2f, bool> PcInput::getInput(gameInput input)
{
	return std::make_pair(readDirection(input._keys), readShoot(input._keys));
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

	if (sf::Keyboard::isKeyPressed(keys[static_cast<int>(Keys::Up)]))
	{
		direction.y = -1;
	}

	return direction;
}

bool PcInput::readShoot(std::vector<sf::Keyboard::Key> keys)
{
	return sf::Keyboard::isKeyPressed(keys[static_cast<int>(Keys::Shoot)]);
}
 