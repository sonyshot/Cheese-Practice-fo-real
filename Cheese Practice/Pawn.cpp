#include "Piece.cpp"

class Pawn : public Piece, public sf::Drawable {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	using Piece::Piece;

	bool legalMove(Board board, std::array<int, 2> move) {
		std::array<int, 2> inBetween;
		inBetween[0] = move[0];
		inBetween[1] = move[1] - 1;
		if ((move[1] == m_position[1] + 1) && (abs(move[0] - m_position[0]) < 2)) {
			if ((move[0] == m_position[0]) && !(board.inSpace(move)->getColor())) {
				return true;
			}
			else if(!(board.inSpace(move)->getColor() + m_color)){
				return true;
			}
			else {
				return false;
			};
		}
		else if (m_position[1] == 1 && m_position[0] == move[0] && move[1] == 3 && !(board.inSpace(move)->getColor()) && !(board.inSpace(inBetween)->getColor())) {
			return true;
		}
		else {
			return false;
		};
	};

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(m_sprite, states);
	};
	//see above
};