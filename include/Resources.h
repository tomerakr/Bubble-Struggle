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
	void playSound(const Objects sound);

private:
	Resources();
	Resources(const Resources&) = delete;
	Resources& operator=(const Resources&) = delete;

	std::vector<sf::Texture> m_backgroundTextures;
	std::vector<std::string> m_backgroundTextureNames = { "menuBackground" };
	std::vector<sf::Texture> m_objectTextures;
	std::vector<std::string> m_objectTextureNames = { "button.png" };

	sf::Font m_font;
	std::vector<std::unique_ptr<sf::SoundBuffer>> m_soundBuffer;
	std::vector<sf::Sound> m_sound;
};

