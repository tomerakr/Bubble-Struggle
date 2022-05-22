#include "Button.h"
#include "Resources.h"

Button::Button(const sf::Vector2f pos, const sf::Vector2f size, const std::string text)
	:GameObject(pos, size, Objects::Button)
{
	auto iconSize = m_icon.getSize();
	m_icon.setFillColor(sf::Color::White);
	m_icon.setTexture(Resources::instance().getObjectTexture(Objects::Button));
	m_icon.setOrigin(iconSize.x / 2, iconSize.y / 2);
	setText(text);
}

void Button::setText(const std::string text)
{
	auto pos = m_icon.getPosition();
	m_text.setPosition(pos.x, pos.y - 8);
	m_text.setColor(sf::Color::White);
	m_text.setFont(*Resources::instance().getFont());
	m_text.setCharacterSize(textSize);
	m_text.setString(text);
	m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
}

const bool Button::isPressed(const sf::Vector2f mousePos) const
{
	return m_icon.getGlobalBounds().contains(mousePos);
}

const bool Button::hover(const sf::Vector2f mousePos)
{
	if (m_icon.getGlobalBounds().contains(mousePos))
	{
		m_icon.setRotation(5);
		m_text.setRotation(5);
		return true;
	}
	return false;
}

void Button::draw(sf::RenderWindow& window)
{
	window.draw(m_icon);
	window.draw(m_text);
}