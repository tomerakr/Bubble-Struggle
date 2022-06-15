#include "Resources.h"
#include <fstream>

constexpr int THEME = 0;

Resources::Resources()
{
	if (!m_font.loadFromFile("Font.ttf"))
	{
		exit(EXIT_FAILURE);
	}

	for (int i = 0; i < static_cast<int>(Sound::MAX); ++i)
	{
		if (!m_soundBuffer[i].loadFromFile(m_soundsNames[i]))
		{
			exit(EXIT_FAILURE);
		}
		m_sound[i].setBuffer(m_soundBuffer[i]);
		m_sound[i].setVolume(50);
	}
	m_sound[THEME].setVolume(10);
	m_sound[THEME].setLoop(true); //theme song

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
	if (index >= 0 && index < m_levels.size())
	{
		return m_levels[index];
	}
	return "";
}

void Resources::playSound(const Sound& sound)
{
	m_sound[static_cast<int>(sound)].play();
}

void Resources::setVolume(int volume)
{
	m_sound[static_cast<int>(Sound::theme)].setVolume(volume * 5);
}