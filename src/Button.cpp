#include "Button.h"

Button::Button(const sf::Vector2f pos, const sf::Vector2f size, const std::string text)
	:GameObject(pos, size, Objects::Button)
{
	setText(text);
}

void Button::setText(const std::string text)
{
	m_text.setPosition(m_icon.getPosition());
	m_text.setString(text);
}

const bool Button::isPressed(const sf::Vector2f mousePos) const
{
	return m_icon.getGlobalBounds().contains(mousePos);
}

const bool Button::hover(const sf::Vector2f mousePos)
{
	if (m_icon.getGlobalBounds().contains(mousePos))
	{
		m_icon.setFillColor(sf::Color::Yellow);
		return true;
	}
	return false;
}