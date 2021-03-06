#pragma once

#include <string>
#include "RectangleObjects.h"

constexpr int TEXT_SIZE = 25;

class Button : public RectangleObjects
{
public:
	Button(const sf::Vector2f& pos, const sf::Vector2f& size, const Objects& texture = Objects::Button, const std::string& text = "");
	void setText		(const std::string& text);
	const bool isPressed(const sf::Vector2f& mousePos) const;
	const bool hover	(const sf::Vector2f& mousePos);
	void resetTilt()		{ m_icon.setRotation(0); m_text.setRotation(0); }
	void draw(sf::RenderWindow& window) const;
	void textSize(int size) { m_text.setCharacterSize(size); }

	//for level creator
	void setColor(const sf::Color& color)	{ m_icon.setFillColor(color); }
	void tilt()								{ m_icon.setRotation(m_icon.getRotation() == 90 ? 0 : 90); flip(); }
	void flip()								{ m_icon.scale(-1, 1); }

private:
	sf::Text m_text;
};
