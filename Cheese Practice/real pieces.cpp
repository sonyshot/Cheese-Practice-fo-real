#include "real pieces.h"
#include "Board.h"

//PAWN----------------------------------------------
bool Pawn::legalMove(Board board, std::array<int, 2> move) {
	std::array<int, 2> inBetween;
	inBetween[0] = move[0];
	inBetween[1] = move[1] - 1;
	if ((move[1] == m_position[1] + 1) && (abs(move[0] - m_position[0]) < 2)) {
		if ((move[0] == m_position[0]) && !(board.inSpace(move)->getColor())) {
			return true;
		}
		else if (!(board.inSpace(move)->getColor() + m_color)) {
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
void Pawn::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
};
	//see above

//KNIGHT----------------------------------------------------------------------------------
bool Knight::legalMove(Board board, std::array<int, 2> move) {
	if (((abs(move[0] - m_position[0]) == 2) && (abs(move[1] - m_position[1] == 1))) || ((abs(move[0] - m_position[0]) == 1) && (abs(move[1] - m_position[1] == 2)))) {
		if (!(board.inSpace(move)->getColor() - m_color))
			return false;
		else
			return true;
	}
	else {
		return false;
	};
};

	//this needs to be redone/actually done
void Knight::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
};
	//see above

//BISHOP-----------------------------------------------------------------------------
bool Bishop::legalMove(Board board, std::array<int, 2> move) {
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
void Bishop::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
};
//see above

//ROOK------------------------------------------------------------------------------------
bool Rook::legalMove(Board board, std::array<int, 2> move) {
	if (move[0] == m_position[0]) {
		int distance = abs(move[1] - m_position[1]);
		int yDir = (move[1] - m_position[1] > 0) - (move[1] - m_position[1] < 0);
		for (int i = 1; i < distance; i++) {
			std::array<int, 2> test = { m_position[0], m_position[1] + i*yDir };
			if (!!(board.inSpace(test)->getColor()))
				return false;
		};
		if (!(board.inSpace(move)->getColor() - m_color))
			return false;
		else
			return true;
	}
	else if (move[1] == m_position[1]) {
		int distance = abs(move[0] - m_position[0]);
		int xDir = (move[0] - m_position[0] > 0) - (move[0] - m_position[0] < 0);
		for (int i = 1; i < distance; i++) {
			std::array<int, 2> test = { m_position[0] + i*xDir, m_position[1] };
			if (!!(board.inSpace(test)->getColor()))
				return false;
		};
		if (!(board.inSpace(move)->getColor() - m_color))
			return false;
		else
			return true;
	}
	else {
		return false;
	}
};

	//this needs to be redone/actually done
void Rook::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
};
	//see above

//QUEEN----------------------------------------------------------------------------------------
bool Queen::legalMove(Board board, std::array<int, 2> move) {
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
	else if (move[0] == m_position[0]) {
		int distance = abs(move[1] - m_position[1]);
		int yDir = (move[1] - m_position[1] > 0) - (move[1] - m_position[1] < 0);
		for (int i = 1; i < distance; i++) {
			std::array<int, 2> test = { m_position[0], m_position[1] + i*yDir };
			if (!!(board.inSpace(test)->getColor()))
				return false;
		};
		if (!(board.inSpace(move)->getColor() - m_color))
			return false;
		else
			return true;
	}
	else if (move[1] == m_position[1]) {
		int distance = abs(move[0] - m_position[0]);
		int xDir = (move[0] - m_position[0] > 0) - (move[0] - m_position[0] < 0);
		for (int i = 1; i < distance; i++) {
			std::array<int, 2> test = { m_position[0] + i*xDir, m_position[1] };
			if (!!(board.inSpace(test)->getColor()))
				return false;
		};
		if (!(board.inSpace(move)->getColor() - m_color))
			return false;
		else
			return true;
	}
	else {
		return false;
	}
};

	//this needs to be redone/actually done
void Queen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
};
	//see above

//KING--------------------------------------------------------------------------------------
bool King::legalMove(Board board, std::array<int, 2> move) {
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
void King::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
};
	//see above

//EMPTY-----------------------------------------------------------------
bool EmptySquare::legalMove(Board board, std::array<int, 2> move) {
	return false;
};

	//this needs to be redone/actually done
void EmptySquare::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
};
	//see above