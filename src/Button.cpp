#include "Button.h"
#include "Resources.h"

Button::Button(const sf::Vector2f& pos, const sf::Vector2f& size, const Objects& texture, const std::string& text)
	:RectangleObjects(pos, size, texture)
{
	m_icon.setOrigin(size.x / 2, size.y / 2);
	if (text.size() > 0)
	{
		setText(text);
	}
}

void Button::setText(const std::string& text)
{
	auto pos = m_icon.getPosition();
	m_text.setPosition(pos.x, pos.y - 5);
	m_text.setFillColor(sf::Color::White);
	m_text.setFont(*Resources::instance().getFont());
	m_text.setCharacterSize(TEXT_SIZE);
	m_text.setString(text);
	m_text.setOrigin(m_text.getGlobalBounds().width / 2, m_text.getGlobalBounds().height / 2);
}

const bool Button::isPressed(const sf::Vector2f& mousePos) const
{
	return m_icon.getGlobalBounds().contains(mousePos);
}

const bool Button::hover(const sf::Vector2f& mousePos)
{
	if (m_icon.getGlobalBounds().contains(mousePos))
	{
		m_icon.setRotation(BUTTON_ROTATION);
		m_text.setRotation(BUTTON_ROTATION);
		return true;
	}
	return false;
}

void Button::draw(sf::RenderWindow& window) const 
{
	window.draw(m_icon);
	window.draw(m_text);
}