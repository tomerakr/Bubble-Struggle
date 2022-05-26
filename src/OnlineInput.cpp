#include "OnlineInput.h"

OnlineInput::OnlineInput()
{

}

std::pair<sf::Vector2f, bool> OnlineInput::getInput(std::vector<sf::Keyboard::Key> keys)
{
	return std::make_pair(sf::Vector2f(0, 0), true);
}