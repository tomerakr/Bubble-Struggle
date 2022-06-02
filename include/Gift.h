#include "MovingObject.h"

#include "Macros.h"
#include "Board.h"

class Gift : public MovingObject
{
public:
	Gift(const sf::Vector2f position, Board* board, const Gifts giftType = Gifts::Freeze);

private:
	Gifts m_giftType;
	Board* m_board;
};