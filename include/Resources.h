#pragma once

#include <vector>
#include "Macros.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class Resources
{
public:
	static Resources& instance();

	const sf::Texture* getTexture(Objects texture);
	void playSound(Objects sound);

private:
	Resources();
	Resources(const Resources&) = delete;

	std::vector<std::unique_ptr<sf::Texture>> m_texture;
	std::vector<std::unique_ptr<sf::SoundBuffer>> m_soundBuffer;
	std::vector<sf::Sound> m_sound;
};

