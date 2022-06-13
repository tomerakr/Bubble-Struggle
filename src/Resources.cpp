#include "Resources.h"
#include <fstream>

Resources::Resources()
{
	if (!m_font.loadFromFile("Font.ttf"))
	{
		exit(EXIT_FAILURE);
	}
	if (!m_soundBuffer[0].loadFromFile("theme.wav"))
	{
		exit(EXIT_FAILURE);
	}
	m_sound[0].setBuffer(m_soundBuffer[0]);
	m_sound[0].setVolume(15);
	m_sound[0].setLoop(true);
	
	readTextureNames();

	m_objectTextures.reserve(static_cast<int>(Objects::MAX));
	for (int i = 0; i < static_cast<int>(Objects::MAX); ++i)
	{
		m_objectTextures.emplace_back();
		if (!m_objectTextures.back().loadFromFile(m_objectTextureNames[i]))
		{ 
			exit(EXIT_FAILURE);
		}
	}

	readLevelsNames();
}

void Resources::readTextureNames()
{
	auto textures = std::ifstream("textureNames.txt");
	if (!textures.is_open())
	{
		exit(EXIT_FAILURE);
	}
	
	auto textureName = std::string();
	std::getline(textures, textureName);

	while (!textureName.empty())
	{
		m_objectTextureNames.push_back(textureName);
		std::getline(textures, textureName);
	} 
}

Resources& Resources::instance()
{
	static Resources inst;
	return inst;
}

sf::Texture* Resources::getObjectTexture(const Objects texture)
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
	return m_levels[static_cast<std::vector<std::string, std::allocator<std::string>>::size_type>(index)];
}

void Resources::playSound(const Sound& sound)
{
	m_sound[static_cast<int>(sound)].play();
}