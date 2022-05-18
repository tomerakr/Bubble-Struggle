#pragma once

#include <vector>
#include "Macros.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Resources
{
public:
	static Resources& instance();

	sf::Texture* const getBackgroundTexture(const Backgrounds texture);
	sf::Texture* const getObjectTexture(const Objects texture);
	
	sf::Color const getColor(const int index) { return m_colors[index]; }
	sf::Font* const getFont() { return &m_font; }

	std::string getLevelName(int index);

	void playSound(const Objects sound);

private:
	Resources();
	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;
	void readLevelsNames();


	std::vector<sf::Texture> m_backgroundTextures;
	std::vector<std::string> m_backgroundTextureNames = { "menuBackground.png" };
	std::vector<sf::Texture> m_objectTextures;
	std::vector<std::string> m_objectTextureNames = { "ball.png", "bear.png", "button.png" };

	sf::Font m_font;
	std::vector<std::unique_ptr<sf::SoundBuffer>> m_soundBuffer;
	std::vector<sf::Sound> m_sound;

	sf::Color m_colors[numOfBalls] = { sf::Color::Cyan, sf::Color::Yellow, sf::Color::Red, sf::Color::Green,
	sf::Color::Magenta, sf::Color::Blue, sf::Color::Black, sf::Color(255, 100, 128), sf::Color(255, 140, 0) };

	std::vector <std::string> m_levels;
};

