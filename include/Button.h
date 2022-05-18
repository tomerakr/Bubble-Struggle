#pragma once

#include <string>
#include "GameObject.h"

constexpr int textSize = 30;

class Button : public GameObject
{
public:
	Button(const sf::Vector2f pos, const sf::Vector2f size, const std::string text);
	void setText(const std::string text);
	const bool isPressed(const sf::Vector2f mousePos) const;
	const bool hover(const sf::Vector2f mousePos);
	void resetColor() { m_icon.setFillColor(sf::Color::White); }
	void draw(sf::RenderWindow& window);

private:
	sf::Text m_text;
};
