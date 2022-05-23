#include "Rope.h"
#include <SFML/Graphics.hpp>

#include <vector>

class Gun
{
public:
	Gun(Objects ropeTexture);
	void shoot(const sf::Vector2f bearPos);
	void update();
	void drawRopes(sf::RenderWindow& window);

private:
	std::vector<Rope> m_ropes;
	int m_maxNumRopes = 1;

};