#include "Piece.cpp"

class Bishop : public Piece, public sf::Drawable {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	using Piece::Piece;

	bool legalMove(Board board, std::array<int, 2> move) {
		if (abs(move[0] - m_position[0]) == abs(move[1] - m_position[1])) {
			int distance = abs(move[0] - m_position[0]);
			int xDir = (move[0] - m_position[0] > 0) - (move[0] - m_position[0] < 0);
			int yDir = (move[1] - m_position[1] > 0) - (move[1] - m_position[1] < 0);
			for (int i = 1; i < distance; i++) {
				std::array<int, 2> test = { m_position[0] + i*xDir, m_position[1] + i*yDir };
				if (!!(board.inSpace(test)->getColor()))
					return false;
			};
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