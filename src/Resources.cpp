#include "Resources.h"

Resources::Resources()
{
	if (!m_font.loadFromFile("GILSANUB.ttf"))
	{
		exit(EXIT_FAILURE);
	}

	m_backgroundTextures.reserve(numOfBackgrounds);
	for (int i = 0; i < numOfBackgrounds; ++i)
	{
		m_backgroundTextures.emplace_back();
		if (!m_backgroundTextures.back().loadFromFile(m_backgroundTextureNames[i]))
		{
			exit(EXIT_FAILURE);
		}
	}

	//m_objectTextures.reserve(numOfObjects);
	//for (int i = 0; i < numOfObjects; ++i)
	//{
	//	m_objectTextures.emplace_back();
	//	if (!m_objectTextures.back().loadFromFile(m_objectTextureNames[i]))
	//	{ 
	//		exit(EXIT_FAILURE);
	//	}
	//}
}

Resources& Resources::instance()
{
	static Resources inst;
	return inst;
}

sf::Texture* const Resources::getBackgroundTexture(const Backgrounds texture)
{
	return &m_backgroundTextures[int(texture)];
}

sf::Texture* const Resources::getObjectTexture(const Objects texture)
{
	return &m_objectTextures[int(texture)];
}