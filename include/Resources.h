#pragma once

#include <vector>
#include "Macros.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Resources
{
public:
	static Resources& instance();

	sf::Texture* getObjectTexture(const Objects texture);
	
	sf::Color& getColor(const int index){ return m_colors[index]; }
	sf::Font* getFont()					{ return &m_font; }
	int getNumOfLevels()				{ return m_levels.size(); }
	std::string getLevelName(int index);
	void playSound(const Sound& sound);
	void setVolume(int volume);

private:
	Resources();
	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;
	void readLevelsNames();
	void readTextureNames();

	std::vector<sf::Texture> m_objectTextures;
	std::vector<std::string> m_objectTextureNames;

	sf::Font m_font;
	sf::SoundBuffer m_soundBuffer[static_cast<int>(Sound::MAX)];
	sf::Sound m_sound[static_cast<int>(Sound::MAX)];
	std::string m_soundsNames[static_cast<int>(Sound::MAX)] = { "theme.wav", "click.wav" };

	sf::Color m_colors[numOfBalls] = {sf::Color(82, 194, 236),  sf::Color(1, 111, 255), sf::Color(198, 111, 239), 
									  sf::Color(248, 135, 230), sf::Color(233, 74, 90), sf::Color(252, 139, 18),
									  sf::Color(254, 194, 34),  sf::Color(151, 216, 0), sf::Color(70, 158, 28) };

	std::vector <std::string> m_levels;
};

