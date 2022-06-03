#include "Rope.h"
#include <SFML/Graphics.hpp>

#include <vector>
class Board;

class Gun
{
public:
	Gun(int ropeTexture, Board* board);
	void shoot(const sf::Vector2f& bearPos);
	void update();
	void drawRopes(sf::RenderWindow& window);

private:
	std::vector<Rope> m_ropes;
	int m_maxRopes = 1;
	Board* m_board;
	int m_ropeTexture;
};