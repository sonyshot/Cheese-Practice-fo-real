
#include "Movelist.h"

Movelist::Movelist(Board * board) {
	m_board = board;

	if (!m_font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
		std::cout << "failed to load font" << std::endl;
	}
	m_text.setFont(m_font);
	m_text.setString(m_printMoves);
	m_text.setFillColor(sf::Color::White);
	m_text.setPosition(800.f, 0.f);


};

Movelist::~Movelist() {
	for (int i = 0; i < m_captureList.size(); i++) {
		delete m_captureList[i];
	}
}

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

std::string Movelist::newSquareNotation(std::array<int, 2> square, ChessMoves specialMove) {
	std::string output;
	switch (specialMove) {

	case ChessMoves::NORMAL:
		output.append(squareName(square));
		return output;
		break;

	case ChessMoves::CASTLE:
		//castle
		if (square[0] == 6)
			output.append("0-0");
		else
			output.append("0-0-0");

		return output;
		break;

	case ChessMoves::PROMOTION:
		//promotion
		output.append("=Q");
		return output;
		break;

	case ChessMoves::ENPASSANT:
		//en passant
		output.append(squareName(square));
		output.append(" e.p.");
		return output;
		break;
	}
}

std::string Movelist::printableString(std::array<std::array<int, 2>, 2> move, Piece* piece, ChessMoves specialMove) {
	std::string output;

	if (piece->getColor() == 1)
		output = "\n";
	else
		output = "-";

	switch(specialMove) {

	case ChessMoves::NORMAL:
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
		break;

	case ChessMoves::CASTLE: 
		//castle--------------------------------------------------------------
		output.append(newSquareNotation(move[1], specialMove));
		return output;
		break;

	case ChessMoves::PROMOTION:
		//promotion------------------------------------------------------------
		if ((m_board->inSpace(move[1])->getColor() == 0) ? 0 : 1)
			output.append(squareName(move[0]).substr(0, 1) + "x");

		output.append(newSquareNotation(move[1], specialMove));
		return output;
		break;

	case ChessMoves::ENPASSANT:
		//en passant-----------------------------------------------------------
		output.append(squareName(move[0]).substr(0, 1));
		output.append("x");
		output.append(newSquareNotation(move[1], specialMove));

		return output;
		break;
	}
}

void Movelist::addToMovelist(std::array<int, 2> currentPos, std::array<int, 2> newPos) {
	
	
	//special moves are indicated in m_moveType vector: 1 - castling; 2 - promotion; 3 - en passant
	if (m_board->inSpace(currentPos)->canCastle(newPos)) {
		m_movelist.push_back({ currentPos, newPos }); //add from-to positions to movelist

		m_captureList.push_back(m_board->inSpace(newPos)); //put captured piece into list
		m_captureList.back()->setCapture(1);
		m_moveType.push_back(ChessMoves::CASTLE);
		m_text.setString(m_printMoves.append(printableString({ currentPos, newPos }, m_board->inSpace(currentPos), ChessMoves::CASTLE)));
	}
	else if (m_board->inSpace(currentPos)->canPromote(newPos)) {
		m_movelist.push_back({ currentPos, newPos }); //add from-to positions to movelist

		m_captureList.push_back(m_board->inSpace(newPos)); 
		m_captureList.back()->setCapture(1);
		m_moveType.push_back(ChessMoves::PROMOTION);
		m_text.setString(m_printMoves.append(printableString({ currentPos, newPos }, m_board->inSpace(currentPos), ChessMoves::PROMOTION)));
	}
	else if (m_board->inSpace(currentPos)->canEnPassant(newPos)) {
		m_movelist.push_back({ currentPos, newPos }); //add from-to positions to movelist

		m_captureList.push_back(m_board->inSpace({ newPos[0], currentPos[1] })); 
		m_captureList.back()->setCapture(1);
		m_moveType.push_back(ChessMoves::ENPASSANT);
		m_text.setString(m_printMoves.append(printableString({ currentPos, newPos }, m_board->inSpace(currentPos), ChessMoves::ENPASSANT)));
	}
	else {
		m_movelist.push_back({ currentPos, newPos }); //add from-to positions to movelist

		m_captureList.push_back(m_board->inSpace(newPos)); 
		m_captureList.back()->setCapture(1);
		m_moveType.push_back(ChessMoves::NORMAL);
		m_text.setString(m_printMoves.append(printableString({ currentPos, newPos }, m_board->inSpace(currentPos), ChessMoves::NORMAL)));
	}
}

void Movelist::removeFromMovelist() {
	//special considerations for moving pieces back into the board are done via undoMove within the board
	//this function simply removes the last entry of each stored list and corrects the movelist text accordingly

	//0-normal move; 1-castling; 2-promotion; 3-en passant
	if (m_moveType.back() == ChessMoves::NORMAL) {
		std::size_t found = m_printMoves.find_last_of("-\n");
		m_printMoves.erase(found, m_printMoves.length() - found);
	}
	else if (m_moveType.back() == ChessMoves::CASTLE) {
		if (m_movelist.back()[1][0] == 6) {
			//kingside castling
			m_printMoves.erase(m_printMoves.length() - 4, 4);
		}
		else
		{
			//queenside castling
			m_printMoves.erase(m_printMoves.length() - 6, 6);
		}

	}
	else if (m_moveType.back() == ChessMoves::PROMOTION) {
		std::size_t found = m_printMoves.find_last_of("-\n");
		m_printMoves.erase(found, m_printMoves.length() - found);
	}
	else if(m_moveType.back() == ChessMoves::ENPASSANT) {
		std::size_t found = m_printMoves.find_last_of("-\n");
		m_printMoves.erase(found, m_printMoves.length() - found);
	}
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

std::string Movelist::hashBoard() {
	std::string key;
	Piece * currentPiece;
	for (int i = 0; i < 64; i++) {
		currentPiece = m_board->m_squares[i];
		key.append(hashPiece(currentPiece));
	}
	if (m_board->turn == 1)
		key.append("+");
	else
		key.append("-");

	return key;
}

std::string Movelist::hashPiece(Piece * piece) {
	std::string output;
	//each component of hash starts with piece 'name'
	if (piece->getName() == "") {
		output.append("P");
	}
	else {
		output.append(piece->getName());
	}
	//add the piece color
	if (piece->getName() != "S")
		output.append(std::to_string(piece->getColor()));

	// extra character for pieces with special moves
	if (piece->getName() == "") {
		if (piece->canEnPassant({ piece->getPosition()[0] - 1, piece->getPosition()[1] + piece->getColor() })) {
			output.append("1"); //en passant left available
		}
		else if (piece->canEnPassant({ piece->getPosition()[0] + 1, piece->getPosition()[1] + piece->getColor() })) {
			output.append("2"); //en passant right available
		}
		else {
			output.append("0"); //can't en passant
		}
	}
	else if (piece->getName() == "R") {
		if (!piece->hasMoved())
			output.append("1"); //can't castle
		else
			output.append("0");
	}
	else if(piece->getName() == "K"){
		if (piece->canCastle({ piece->getPosition()[0] + 2, piece->getPosition()[1] }))
			output.append("1"); //castle right
		else if (piece->canCastle({ piece->getPosition()[0] - 2, piece->getPosition()[1] }))
			output.append("2"); //castle left
		else
			output.append("0"); //can't castle
	}
	return output;
}