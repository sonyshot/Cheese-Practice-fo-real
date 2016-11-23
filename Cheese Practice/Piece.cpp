#include "Board.cpp"

class Piece{
protected:
	std::array<int, 2> m_position;
	int m_color;
	sf::Sprite m_sprite;
public:
	Piece() {
		m_position = { 0, 0 };
		m_color = 1;
	};

	Piece(int file, int rank, int color) {
		m_position = { file, rank };

		//-1 for black, 1 for white, 0 for empty square
		m_color = color;
	};

	std::array<int, 2> getPosition() {
		return m_position;
	};

	void move(std::array<int, 2> newPos) {
		m_position.swap(newPos);
	};

	int getColor() {
		return m_color;
	};

	virtual bool legalMove(Board board, std::array<int, 2> move)
/*		switch (abs(m_pieceType)) {
		case 0:
			//empty square
			break;
		case 1:
			//pawn
			break;
		case 2:
			//knight
			break;
		case 3:
			//bishop
			break;
		case 4:
			//rook
			break;
		case 5:
			//queen
			break;
		case 6:
			//king
			break;
		};
		*/
	 = 0;
};