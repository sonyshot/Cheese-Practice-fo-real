#include "Piece.cpp"

class King : public Piece, public sf::Drawable {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	using Piece::Piece;

	bool legalMove(Board board, std::array<int, 2> move) {
		if ((abs(move[0] - m_position[0]) <= 1) && (abs(move[1] - m_position[1]) <= 1)) {
			if (!(board.inSpace(move)->getColor() - m_color))
				return false;
			else
				return true;
		}
		else
			return false;
	};

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(m_sprite, states);
	};
	//see above
};