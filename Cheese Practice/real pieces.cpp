
#include "real pieces.h"
#include "Board.h"

//PAWN----------------------------------------------
Pawn::Pawn(int size, int file, int rank, int color, sf::Texture * texture, Board * board) :Piece(size, file, rank, color, texture, board, "") {};

bool Pawn::legalMove(std::array<int, 2> move, Board * bufferBoard) {
	if (m_currentBoard->turn != m_color) {
		std::cout << "wrong turn" << std::endl;
		return false;
	}

	if (move == m_position)
		return false;

	if (bufferBoard != NULL) {
		bufferBoard->movePiece(m_position, move);
		if (bufferBoard->coveredSquare(bufferBoard->kingPosition(m_color), -1 * m_color).size() != 0) {
			bufferBoard->undoMove();
			return false;
		}
		bufferBoard->undoMove();
	}
	if (canEnPassant(move))
		return true;
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
};

void Pawn::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
	if (m_isHovered) {
		target.draw(m_highlightCircle, states);
	}
};

bool Pawn::canPromote(std::array<int, 2> move) {
	if (move[1] == 3.5 + m_color*3.5)
		return true;
	else
		return false;
};

bool Pawn::canEnPassant(std::array<int, 2> move) {
	//if piece on either side is a pawn and the previous move was two squares in length and ended on the square adjacent
	if (m_currentBoard->inSpace({ move[0], m_position[1] })->getName() == "" && m_currentBoard->previousMove()[0] == std::array<int, 2> {move[0], move[1] + m_color} && m_currentBoard->previousMove()[1] == std::array<int, 2> {move[0], move[1] - m_color})
		return true;
	else
		return false;
};

std::vector<std::array<int, 2>> Pawn::listLegalMoves(Board * bufferBoard) {
	std::vector<std::array<int, 2>> output;
	for (int i = -1; i < 2; i++) {
		if (m_position[0] + i >= 0 && m_position[0] + i <= 7) {
			if (legalMove({ m_position[0] + i, m_position[1] + m_color }, bufferBoard)) {
				output.push_back({ m_position[0] + i, m_position[1] + m_color });
			}
		}
	}
	if (m_position[1] == 1 && legalMove({ m_position[0], m_position[1] + 2 }, bufferBoard)) {
		output.push_back({ m_position[0], m_position[1] + 2 });
	}
	return output;
}

//KNIGHT----------------------------------------------------------------------------------
Knight::Knight(int size, int file, int rank, int color, sf::Texture * texture, Board * board) :Piece(size, file, rank, color, texture, board, "N") {

};

bool Knight::legalMove(std::array<int, 2> move, Board * bufferBoard) {
	if (m_currentBoard->turn != m_color) {
		std::cout << "wrong turn" << std::endl;
		return false;
	}
	if (move == m_position)
		return false;

	if (bufferBoard != NULL) {
		bufferBoard->movePiece(m_position, move);
		if (bufferBoard->coveredSquare(bufferBoard->kingPosition(m_color), -1 * m_color).size() != 0) {
			bufferBoard->undoMove();
			return false;
		}
		bufferBoard->undoMove();
	}
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

std::vector<std::array<int, 2>> Knight::listLegalMoves(Board * bufferBoard) {
	std::vector<std::array<int, 2>> output;
	for (int i = 1; i < 12; i++) {
		if (i % 3 != 0) {
			int testX = (int)(m_position[0] + 2.23607*cos(i*3.1415926 / 6.0) + 0.5);
			int testY = (int)(m_position[1] + 2.23607*sin(i*3.1415926 / 6.0) + 0.5);
			if ((testX < 8 && testX >= 0) && (testY < 8 && testY >= 0)) {
				if (legalMove({ testX, testY }, bufferBoard)) {
					output.push_back({ testX, testY });
				}
			}
		}
	}
	return output;
}

void Knight::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
};

//BISHOP-----------------------------------------------------------------------------
Bishop::Bishop(int size, int file, int rank, int color, sf::Texture * texture, Board * board) :Piece(size, file, rank, color, texture, board, "B") {

};

bool Bishop::legalMove(std::array<int, 2> move, Board * bufferBoard) {
	if (m_currentBoard->turn != m_color) {
		std::cout << "wrong turn" << std::endl;
		return false;
	}
	if (move == m_position)
		return false;

	if (bufferBoard != NULL) {
		bufferBoard->movePiece(m_position, move);
		if (bufferBoard->coveredSquare(bufferBoard->kingPosition(getColor()), -1 * getColor()).size() != 0) {
			bufferBoard->undoMove();
			return false;
		}
		bufferBoard->undoMove();
	}
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

std::vector<std::array<int, 2>> Bishop::listLegalMoves(Board * bufferBoard) {
	std::vector<std::array<int, 2>> output;
	int posX = 7 - m_position[0];
	int posY = 7 - m_position[1];
	for (int i = 1; i <= std::min(posX, posY); i++) {
		if (legalMove({ m_position[0] + i, m_position[1] + i }, bufferBoard)) {
			output.push_back({ m_position[0] + i, m_position[1] + i });
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= std::min(m_position[0], posY); i++) {
		if (legalMove({ m_position[0] - i, m_position[1] + i }, bufferBoard)) {
			output.push_back({ m_position[0] - i, m_position[1] + i });
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= std::min(m_position[0], m_position[1]); i++) {
		if (legalMove({ m_position[0] - i, m_position[1] - i }, bufferBoard)) {
			output.push_back({ m_position[0] - i, m_position[1] - i });
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= std::min(posX, m_position[1]); i++) {
		if (legalMove({ m_position[0] + i, m_position[1] - i }, bufferBoard)) {
			output.push_back({ m_position[0] + i, m_position[1] - i });
		}
		else {
			break;
		}
	}
	return output;
}

void Bishop::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
};

//ROOK------------------------------------------------------------------------------------
Rook::Rook(int size, int file, int rank, int color, sf::Texture * texture, Board * board) :Piece(size, file, rank, color, texture, board, "R") {

};

bool Rook::legalMove(std::array<int, 2> move, Board * bufferBoard) {
	if (m_currentBoard->turn != m_color) {
		std::cout << "wrong turn" << std::endl;
		return false;
	}
	if (move == m_position)
		return false;

	if (bufferBoard != NULL) {
		bufferBoard->movePiece(m_position, move);
		if (bufferBoard->coveredSquare(bufferBoard->kingPosition(getColor()), -1 * getColor()).size() != 0) {
			bufferBoard->undoMove();
			return false;
		}
		bufferBoard->undoMove();
	}
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

std::vector<std::array<int, 2>> Rook::listLegalMoves(Board * bufferBoard) {
	std::vector<std::array<int, 2>> output;
	int posX = 7 - m_position[0];
	int posY = 7 - m_position[1];
	for (int i = 1; i <= posX; i++) {
		if (legalMove({ m_position[0] + i, m_position[1] }, bufferBoard)) {
			output.push_back({ m_position[0] + i, m_position[1] });
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= posY; i++) {
		if (legalMove({ m_position[0], m_position[1] + i }, bufferBoard)) {
			output.push_back({ m_position[0], m_position[1] + i });
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= m_position[0]; i++) {
		if (legalMove({ m_position[0] - i, m_position[1] }, bufferBoard)) {
			output.push_back({ m_position[0] - i, m_position[1] });
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= m_position[1]; i++) {
		if (legalMove({ m_position[0], m_position[1] - i }, bufferBoard)) {
			output.push_back({ m_position[0], m_position[1] - i });
		}
		else {
			break;
		}
	}
	return output;
}

void Rook::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
};

//QUEEN----------------------------------------------------------------------------------------
Queen::Queen(int size, int file, int rank, int color, sf::Texture * texture, Board * board) :Piece(size, file, rank, color, texture, board, "Q") {

};

bool Queen::legalMove(std::array<int, 2> move, Board * bufferBoard) {
	if (m_currentBoard->turn != m_color) {
		std::cout << "wrong turn" << std::endl;
		return false;
	}
	if (move == m_position)
		return false;

	if (bufferBoard != NULL) {
		bufferBoard->movePiece(m_position, move);
		if (bufferBoard->coveredSquare(bufferBoard->kingPosition(m_color), -1 * m_color).size() != 0) {
			bufferBoard->undoMove();
			return false;
		}
		bufferBoard->undoMove();
	}
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

std::vector<std::array<int, 2>> Queen::listLegalMoves(Board * bufferBoard) {
	std::vector<std::array<int, 2>> output;
	int posX = 7 - m_position[0];
	int posY = 7 - m_position[1];
	for (int i = 1; i <= std::min(posX, posY); i++) {
		if (legalMove({ m_position[0] + i, m_position[1] + i }, bufferBoard)) {
			output.push_back({ m_position[0] + i, m_position[1] + i });
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= std::min(m_position[0], posY); i++) {
		if (legalMove({ m_position[0] - i, m_position[1] + i }, bufferBoard)) {
			output.push_back({ m_position[0] - i, m_position[1] + i });
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= std::min(m_position[0], m_position[1]); i++) {
		if (legalMove({ m_position[0] - i, m_position[1] - i }, bufferBoard)) {
			output.push_back({ m_position[0] - i, m_position[1] - i });
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= std::min(posX, m_position[1]); i++) {
		if (legalMove({ m_position[0] + i, m_position[1] - i }, bufferBoard)) {
			output.push_back({ m_position[0] + i, m_position[1] - i });
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= posX; i++) {
		if (legalMove({ m_position[0] + i, m_position[1] }, bufferBoard)) {
			output.push_back({ m_position[0] + i, m_position[1] });
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= posY; i++) {
		if (legalMove({ m_position[0], m_position[1] + i }, bufferBoard)) {
			output.push_back({ m_position[0], m_position[1] + i });
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= m_position[0]; i++) {
		if (legalMove({ m_position[0] - i, m_position[1] }, bufferBoard)) {
			output.push_back({ m_position[0] - i, m_position[1] });
		}
		else {
			break;
		}
	}
	for (int i = 1; i <= m_position[1]; i++) {
		if (legalMove({ m_position[0], m_position[1] - i }, bufferBoard)) {
			output.push_back({ m_position[0], m_position[1] - i });
		}
		else {
			break;
		}
	}
	return output;
}

void Queen::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
};

//KING--------------------------------------------------------------------------------------
King::King(int size, int file, int rank, int color, sf::Texture * texture, Board * board) :Piece(size, file, rank, color, texture, board, "K") {

};

bool King::legalMove(std::array<int, 2> move, Board * bufferBoard) {
	if (m_currentBoard->turn != m_color) {
		std::cout << "wrong turn" << std::endl;
		return false;
	}
	if (move == m_position)
		return false;

	if (bufferBoard != NULL) {
		bufferBoard->movePiece(m_position, move);
		if (bufferBoard->coveredSquare(bufferBoard->kingPosition(m_color), -1 * m_color).size() != 0) {
			bufferBoard->undoMove();
			return false;
		}
		bufferBoard->undoMove();
	}
	if (canCastle(move))
		return true;
	else if ((abs(move[0] - m_position[0]) <= 1) && (abs(move[1] - m_position[1]) <= 1)) {
		if (!(m_currentBoard->inSpace(move)->getColor() - m_color))
			return false;
		else
			return true;
	}
	else
		return false;
};

std::vector<std::array<int, 2>> King::listLegalMoves(Board * bufferBoard) {
	std::vector<std::array<int, 2>> output;
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (i || j) {
				if (legalMove({ m_position[0] + i, m_position[1] + j }, bufferBoard)) {
					output.push_back({ m_position[0] + i, m_position[1] + j });
				}
			}
		}
	}
	return output;
}

void King::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
};

bool King::canCastle(std::array<int, 2> move) {
	if (!hasMoved()) {
		if (move[0] == 6 && !(m_currentBoard->inSpace({ 7, (int)(3.5 - 3.5*m_color) })->hasMoved())) {
			if (!m_currentBoard->inSpace({ 5, (int)(3.5 - 3.5*m_color) })->getColor() && !m_currentBoard->inSpace({ 6, (int)(3.5 - 3.5*m_color) })->getColor()) {
				for (int i = 0; i < 2; i++) {
					if (m_currentBoard->coveredSquare({ 4 + i, (int)(3.5 - 3.5*m_color) }, -1*m_color).size() != 0)
						return false;
				};
				return true;
			}
			else
				return false;
		}
		else if(move[0] == 2 && !m_currentBoard->inSpace({ 0, (int)(3.5 - 3.5*m_color) })->hasMoved()){
			if (!m_currentBoard->inSpace({ 1, (int)(3.5 - 3.5*m_color) })->getColor() && !m_currentBoard->inSpace({ 2, (int)(3.5 - 3.5*m_color) })->getColor() && !m_currentBoard->inSpace({ 3, (int)(3.5 - 3.5*m_color) })->getColor()) {
				for (int i = 0; i < 3; i++) {
					if (m_currentBoard->coveredSquare({ 1 + i, (int)(3.5 - 3.5*m_color) }, -1*m_color).size() != 0)
						return false;
				};
				return true;
			}
			else
				return false;
		}
		else
			return false;
	}
	else
		return false;
};

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
	m_name = "S";
};

bool EmptySquare::legalMove(std::array<int, 2> move, Board * bufferBoard) {
	return false;
};

std::vector<std::array<int, 2>> EmptySquare::listLegalMoves(Board * bufferBoard) {
	std::vector<std::array<int, 2>> output;
	return output;
}

void EmptySquare::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
};
	