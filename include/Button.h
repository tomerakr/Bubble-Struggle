#pragma once

#include <string>
#include "GameObject.h"

class Button : public GameObject
{
public:
	Button(const sf::Vector2f pos, const sf::Vector2f size, const std::string text);
	void setText(const std::string text);
	const bool isPressed(const sf::Vector2f mousePos) const;

private:
	sf::Text m_text;
};
