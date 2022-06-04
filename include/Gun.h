#include "Rope.h"
#include <SFML/Graphics.hpp>

#include <vector>
class Board;

class Gun
{
public:
	Gun(int ropeTexture, Board* board);
	void shoot(const sf::Vector2f& bearPos, const bool freezeRope);
	void update();
	void drawRopes(sf::RenderWindow& window);
	void incMaxRopes() { m_maxRopes++; }

private:
	std::vector<Rope> m_ropes;
	int m_maxRopes = 1;
	Board* m_board;
	int m_ropeTexture;

	const float m_coolDown = 0.5f;
	float m_timeFromLastShot = 0;

	sf::Clock m_clock;
};