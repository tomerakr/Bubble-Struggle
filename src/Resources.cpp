#include "Resources.h"
#include <fstream>

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

	m_objectTextures.reserve(numOfObjects);
	for (int i = 0; i < numOfObjects; ++i)
	{
		m_objectTextures.emplace_back();
		if (!m_objectTextures.back().loadFromFile(m_objectTextureNames[i]))
		{ 
			exit(EXIT_FAILURE);
		}
	}

	readLevelsNames();
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

void Resources::readLevelsNames()
{
	auto levels = std::ifstream("LevelsNames.txt");
	if (!levels.is_open())
	{
		exit(EXIT_FAILURE);
	}

	std::string levelName;
	std::getline(levels, levelName);

	while (!levelName.empty())
	{
		m_levels.push_back(levelName);
		std::getline(levels, levelName);
	}

	levels.close();


}

std::string Resources::getLevelName(int index)
{
	return m_levels[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(index) - 1];
}