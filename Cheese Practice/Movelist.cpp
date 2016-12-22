#include "Movelist.h"

Movelist::Movelist() {
	if (!m_font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
		std::cout << "failed to load font" << std::endl;
	}
	m_text.setFont(m_font);
	m_text.setString(m_printMoves);
	m_text.setFillColor(sf::Color::White);
	m_text.setPosition(800.f, 0.f);


};

std::string Movelist::squareName(std::array<int, 2> square) {
	std::string output;

	switch (square[0]) {
	case 0:
		output.append("a");
		break;
	case 1:
		output.append("b");
		break;
	case 2:
		output.append("c");
		break;
	case 3:
		output.append("d");
		break;
	case 4:
		output.append("e");
		break;
	case 5:
		output.append("f");
		break;
	case 6:
		output.append("g");
		break;
	case 7:
		output.append("h");
		break;
	};
	output.append(std::to_string(square[1] + 1));
	return output;
};

std::string Movelist::newSquareNotation(std::array<int, 2> square, int specialMove) {
	std::string output;
	if (!specialMove) {
		output.append(squareName(square));
		return output;
	}
	else if (specialMove == 1) {
		//castle
		if (square[0] == 6) {
			output.append("0-0");
			return output;
		}
		else {
			output.append("0-0-0");
			return output;
		}
	}
	else if (specialMove == 2) {
		//promotion
		output.append("=Q");
		return output;
	}
	else {
		//en passant
		output.append(squareName(square));
		output.append(" e.p.");
		return output;
	}
}

std::string Movelist::printableString(std::array<std::array<int, 2>, 2> move, Piece* piece, int specialMove) {
	std::string output;

	if (piece->getColor() == 1)
		output = "\n";
	else
		output = "-";

	if (!specialMove) {

		if ((m_board->inSpace(move[1])->getColor() == 0) ? 0 : 1) {
			if (piece->getName() == "")
				output.append(squareName(move[0]).substr(0, 1));
			else
				output.append(piece->getName());

			output.append("x");
		}
		else {
			output.append(piece->getName());
		}
		output.append(newSquareNotation(move[1], specialMove));
		return output;
	}
	else if (specialMove == 1) {
		//castle--------------------------------------------------------------
		output.append(newSquareNotation(move[1], specialMove));
		return output;
	}
	else if (specialMove == 2) {
		//promotion------------------------------------------------------------
		if ((m_board->inSpace(move[1])->getColor() == 0) ? 0 : 1)
			output.append(squareName(move[0]).substr(0, 1) + "x");

		output.append(newSquareNotation(move[1], specialMove));
		return output;
	}
	else if (specialMove == 3) {
		//en passant-----------------------------------------------------------
		output.append(squareName(move[0]).substr(0, 1));
		output.append("x");
		output.append(newSquareNotation(move[1], specialMove));

		return output;
	}
}

void Movelist::addToMovelist(std::array<int, 2> currentPos, std::array<int, 2> newPos) {
	std::cout << this << std::endl;
	m_movelist.push_back({ currentPos, newPos }); //add from-to positions to movelist
	m_captureList.push_back(m_board->inSpace(newPos)); //put captured piece into list

	//special moves are indicated in m_moveType vector: 1 - castling; 2 - promotion; 3 - en passant
	if (m_board->inSpace(currentPos)->canCastle(newPos)) {
		m_moveType.push_back(1);
		m_text.setString(m_printMoves.append(printableString({ currentPos, newPos }, m_board->inSpace(currentPos), 1)));
	}
	else if (m_board->inSpace(currentPos)->canPromote(newPos)) {
		m_moveType.push_back(2);
		m_text.setString(m_printMoves.append(printableString({ currentPos, newPos }, m_board->inSpace(currentPos), 2)));
	}
	else if (m_board->inSpace(currentPos)->canEnPassant(newPos)) {
		m_moveType.push_back(3);
		m_text.setString(m_printMoves.append(printableString({ currentPos, newPos }, m_board->inSpace(currentPos), 3)));
	}
	else {
		m_moveType.push_back(0);
		m_text.setString(m_printMoves.append(printableString({ currentPos, newPos }, m_board->inSpace(currentPos), 0)));
	}
}

void Movelist::removeFromMovelist() {
	//put piece pointer from capturelist back into Board m_squares
	//^^ handled in undomove of board.cpp

	//will be updated to look for move type, mostly for castling
	std::size_t found = m_printMoves.find_last_of("-\n");
	m_printMoves.erase(found, m_printMoves.length() - found);
	m_text.setString(m_printMoves);

	m_movelist.pop_back();
	m_captureList.pop_back();
	m_moveType.pop_back();
}

std::array<std::array<int, 2>, 2> Movelist::previousMove() {
	if (m_movelist.size() == 0) {
		std::array<int, 2> zeros = { 0, 0 };
		return std::array<std::array<int, 2>, 2> { zeros, zeros };
	}
	else {
		return m_movelist.back();
	}
}

void Movelist::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_text, states);
}