#include "real pieces.h"
#include "Board.h"

//PAWN----------------------------------------------
Pawn::Pawn(int size, int file, int rank, int color, sf::Texture * texture, Board * board) :Piece(size, file, rank, color, texture, board, "") {};

bool Pawn::legalMove(std::array<int, 2> move) {
	std::array<int, 2> inBetween;
	inBetween[0] = move[0];
	inBetween[1] = move[1] - m_color;
	if ((move[1] == m_position[1] + m_color) && (abs(move[0] - m_position[0]) < 2)) {
		if ((move[0] == m_position[0]) && !(m_currentBoard->inSpace(move)->getColor())) {
			return true;
		}
		else if (!(m_currentBoard->inSpace(move)->getColor() + m_color)) {
			return true;
		}
		else {
			return false;
		};
	}
	else if (m_position[1] == 3.5 - m_color*2.5 && m_position[0] == move[0] && move[1] == m_position[1] + m_color*2 && !(m_currentBoard->inSpace(move)->getColor()) && !(m_currentBoard->inSpace(inBetween)->getColor())) {
		return true;
	}
	else {
		return false;
	};
}; // also need to add en passant and promotion

void Pawn::move(std::array<int, 2> move) {
	m_position.swap(move);
	m_sprite.setPosition(sf::Vector2f(m_position[0] * m_size, (7 - m_position[1])*m_size));
};


void Pawn::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
};

//KNIGHT----------------------------------------------------------------------------------
Knight::Knight(int size, int file, int rank, int color, sf::Texture * texture, Board * board) :Piece(size, file, rank, color, texture, board, "N") {

};

bool Knight::legalMove(std::array<int, 2> move) {
	if (((abs(move[0] - m_position[0]) == 2) && (abs(move[1] - m_position[1]) == 1)) || ((abs(move[0] - m_position[0]) == 1) && (abs(move[1] - m_position[1]) == 2))) {
		if (!(m_currentBoard->inSpace(move)->getColor() - m_color))
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
Bishop::Bishop(int size, int file, int rank, int color, sf::Texture * texture, Board * board) :Piece(size, file, rank, color, texture, board, "B") {

};

bool Bishop::legalMove(std::array<int, 2> move) {
	if (abs(move[0] - m_position[0]) == abs(move[1] - m_position[1])) {
		int distance = abs(move[0] - m_position[0]);
		int xDir = (move[0] - m_position[0] > 0) - (move[0] - m_position[0] < 0);
		int yDir = (move[1] - m_position[1] > 0) - (move[1] - m_position[1] < 0);
		for (int i = 1; i < distance; i++) {
			std::array<int, 2> test = { m_position[0] + i*xDir, m_position[1] + i*yDir };
			if (!!(m_currentBoard->inSpace(test)->getColor()))
				return false;
		};
		if (!(m_currentBoard->inSpace(move)->getColor() - m_color))
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
Rook::Rook(int size, int file, int rank, int color, sf::Texture * texture, Board * board) :Piece(size, file, rank, color, texture, board, "R") {

};

bool Rook::legalMove(std::array<int, 2> move) {
	if (move[0] == m_position[0]) {
		int distance = abs(move[1] - m_position[1]);
		int yDir = (move[1] - m_position[1] > 0) - (move[1] - m_position[1] < 0);
		for (int i = 1; i < distance; i++) {
			std::array<int, 2> test = { m_position[0], m_position[1] + i*yDir };
			if (!!(m_currentBoard->inSpace(test)->getColor()))
				return false;
		};
		if (!(m_currentBoard->inSpace(move)->getColor() - m_color))
			return false;
		else
			return true;
	}
	else if (move[1] == m_position[1]) {
		int distance = abs(move[0] - m_position[0]);
		int xDir = (move[0] - m_position[0] > 0) - (move[0] - m_position[0] < 0);
		for (int i = 1; i < distance; i++) {
			std::array<int, 2> test = { m_position[0] + i*xDir, m_position[1] };
			if (!!(m_currentBoard->inSpace(test)->getColor()))
				return false;
		};
		if (!(m_currentBoard->inSpace(move)->getColor() - m_color))
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
Queen::Queen(int size, int file, int rank, int color, sf::Texture * texture, Board * board) :Piece(size, file, rank, color, texture, board, "Q") {

};

bool Queen::legalMove(std::array<int, 2> move) {
	if (abs(move[0] - m_position[0]) == abs(move[1] - m_position[1])) {
		int distance = abs(move[0] - m_position[0]);
		int xDir = (move[0] - m_position[0] > 0) - (move[0] - m_position[0] < 0);
		int yDir = (move[1] - m_position[1] > 0) - (move[1] - m_position[1] < 0);
		for (int i = 1; i < distance; i++) {
			std::array<int, 2> test = { m_position[0] + i*xDir, m_position[1] + i*yDir };
			if (!!(m_currentBoard->inSpace(test)->getColor()))
				return false;
		};
		if (!(m_currentBoard->inSpace(move)->getColor() - m_color))
			return false;
		else
			return true;
	}
	else if (move[0] == m_position[0]) {
		int distance = abs(move[1] - m_position[1]);
		int yDir = (move[1] - m_position[1] > 0) - (move[1] - m_position[1] < 0);
		for (int i = 1; i < distance; i++) {
			std::array<int, 2> test = { m_position[0], m_position[1] + i*yDir };
			if (!!(m_currentBoard->inSpace(test)->getColor()))
				return false;
		};
		if (!(m_currentBoard->inSpace(move)->getColor() - m_color))
			return false;
		else
			return true;
	}
	else if (move[1] == m_position[1]) {
		int distance = abs(move[0] - m_position[0]);
		int xDir = (move[0] - m_position[0] > 0) - (move[0] - m_position[0] < 0);
		for (int i = 1; i < distance; i++) {
			std::array<int, 2> test = { m_position[0] + i*xDir, m_position[1] };
			if (!!(m_currentBoard->inSpace(test)->getColor()))
				return false;
		};
		if (!(m_currentBoard->inSpace(move)->getColor() - m_color))
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
King::King(int size, int file, int rank, int color, sf::Texture * texture, Board * board) :Piece(size, file, rank, color, texture, board, "K") {

};

bool King::legalMove(std::array<int, 2> move) {
	if ((abs(move[0] - m_position[0]) <= 1) && (abs(move[1] - m_position[1]) <= 1)) {
		if (!(m_currentBoard->inSpace(move)->getColor() - m_color))
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
EmptySquare::EmptySquare() {
	m_position = { 0, 0 };
	m_color = 0;
};

EmptySquare::EmptySquare(int size, const sf::Texture * texture) {
	m_position = { 0, 0 };
	m_color = 0;
};

EmptySquare::EmptySquare(int size, int file, int rank, int color, const sf::Texture * texture, Board * board) {
	m_position = { file, rank };
	m_color = 0;
	m_currentBoard = board;
};

bool EmptySquare::legalMove(std::array<int, 2> move) {
	return false;
};

	//this needs to be redone/actually done
void EmptySquare::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
};
	//see above