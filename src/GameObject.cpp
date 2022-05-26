#include "GameObject.h"

GameObject::GameObject(const sf::Vector2f pos, const sf::Vector2f size, const Objects texture, const sf::Color color)
{
	m_icon.setSize(size);
	m_icon.setPosition(pos);
	//m_icon.setFillColor(color);
	//m_icon.setTexture(ResourcesManager::instance().getIcon(object));
}

void GameObject::draw(sf::RenderWindow& window)
{
    window.draw(m_icon);
}
