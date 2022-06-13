#include "Animation.h"

Animation::Animation(sf::Vector2u imageCount, const float swicthTime)
	: m_imgaeCount(imageCount), m_switchTime(swicthTime)
{
	m_totalTime = 0.0f;
	m_currentImage.x = 0;
	m_currentImage.y = 0;
}

void Animation::changeTexture(const sf::Texture* const texture, int row)
{
	m_uvRect.width = texture->getSize().x / float(m_imgaeCount.x);
	m_uvRect.height = texture->getSize().y / float(m_imgaeCount.y);
	m_uvRect.top = m_uvRect.height * row;
}

void Animation::update(float deltaTime, bool faceLeft, bool standing)
{
	m_totalTime += deltaTime;

	if (standing)
	{
		m_currentImage.x = 0;
	}
	else if (m_totalTime >= m_switchTime)
	{
		m_totalTime -= m_switchTime;
		++m_currentImage.x;

		if (m_currentImage.x >= m_imgaeCount.x)
		{
			m_currentImage.x = 1;
		}
	}

	m_uvRect.left = (m_currentImage.x + (faceLeft ? 1 : 0)) * std::abs(m_uvRect.width);
	m_uvRect.width = (faceLeft ? -1 : 1) * std::abs(m_uvRect.width);
}
