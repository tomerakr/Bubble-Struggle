#include "Gift.h"


Gift::Gift(const sf::Vector2f position, Board* board, const Gifts giftType)
	:MovingObject(position, sf::Vector2f(50, 50), Objects::Bear), m_giftType(giftType),
		m_board(board)
{

}