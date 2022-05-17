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
		if (!m_backgroundTextures[i].loadFromFile(m_fileBackground[i]))
		{
			exit(EXIT_FAILURE);
		}
	}
}