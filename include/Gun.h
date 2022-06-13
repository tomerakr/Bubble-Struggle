#include "Rope.h"
#include <SFML/Graphics.hpp>

#include <vector>
class Board;

class Gun
{
public:
	Gun(int ropeTexture, Board* board);
	void shoot(const sf::Vector2f& bearPos);
	bool update();
	void freeze() { m_freeze = true; }
	void drawRopes(sf::RenderWindow& window);
	void incMaxRopes() { ++m_maxRopes; }

private:
	std::vector<Rope> m_ropes;
	int m_maxRopes = 1;
	int m_ropeTexture;
	Board* m_board;

	const float m_coolDown = 0.5f;
	float m_timeFromLastShot = 0;
	bool m_freeze = false;
	sf::Clock m_clock;
};