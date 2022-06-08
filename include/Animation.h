   #pragma once

#include "SFML/Graphics.hpp"

class Animation
{
public:
	Animation(const sf::Vector2u imageCount, const float swicthTime);
	
	void update(float deltaTime, bool faceLeft, bool standing);
	void changeTexture(const sf::Texture* const texture, int row);
	sf::IntRect getUvRect() { return m_uvRect; }

private:
	sf::IntRect m_uvRect;
	sf::Vector2u m_imgaeCount;
	sf::Vector2u m_currentImage;
	float m_totalTime;
	float m_switchTime;
};

