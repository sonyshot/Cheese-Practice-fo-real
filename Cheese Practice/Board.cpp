#include "Board.h"
#include "real pieces.h"
#include "array conversion therapy.h"

//buffer board constructor
Board::Board() {
	for (int i = 0; i < 8; i++) {//create pawns on the board
		m_squares[8 + i] = new Pawn(0, i, 1, 1, m_pawnTexture, this);
		std::cout << "white pawn " << i << " created at (" << i << ", " << 1 << ")" << std::endl;
		m_squares[48 + i] = new Pawn(0, i, 6, -1, m_pawnTexture, this);
	};
	for (int i = 0; i < 2; i++) {
		//knights
		m_squares[1 + i * 5] = new Knight(0, 1 + 5 * i, 0, 1, m_knightTexture, this);
		std::cout << "white knight " << i << " created at (" << (1 + 5 * i) << ", " << 0 << ")" << std::endl;
		m_squares[57 + i * 5] = new Knight(0, 1 + 5 * i, 7, -1, m_knightTexture, this);
		//bishops
		m_squares[2 + i * 3] = new Bishop(0, 2 + 3 * i, 0, 1, m_bishopTexture, this);
		m_squares[58 + i * 3] = new Bishop(0, 2 + 3 * i, 7, -1, m_bishopTexture, this);
		//rooks
		m_squares[7 * i] = new Rook(0, 7 * i, 0, 1, m_rookTexture, this);
		m_squares[56 + 7 * i] = new Rook(0, 7 * i, 7, -1, m_rookTexture, this);
	};
	for (int i = 0; i < 1; i++) {
		//queens
		m_squares[3] = new Queen(0, 3, 0, 1, m_queenTexture, this);
		m_squares[59] = new Queen(0, 3, 7, -1, m_queenTexture, this);
		//kings
		m_whiteKingPos = { 4, 0 };
		m_blackKingPos = { 4, 7 };
		m_squares[4] = new King(0, 4, 0, 1, m_kingTexture, this);
		m_squares[60] = new King(0, 4, 7, -1, m_kingTexture, this);
	};

	for (int i = 0; i < 32; i++) {//fill the rest of the board with empty squares
		m_squares[16 + i] = new EmptySquare(100, i % 8, 2 + i / 8, 0, m_kingTexture, this);
	};
};

Board::Board(int size, Board * bufferBoard) {
	//size should be a multiple of 8, not sure how it will draw otherwise
	m_buffer = bufferBoard;

	sf::Image blackSquare;
	blackSquare.create(size / 8, size / 8, sf::Color(50, 50, 50, 255));
	sf::Image whiteSquare;
	whiteSquare.create(size / 8, size / 8, sf::Color(200, 200, 200, 255));

	m_boardTexture.create(size, size);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((i + j) % 2 == 0)
				m_boardTexture.update(whiteSquare, i*size / 8, j*size / 8);
			else
				m_boardTexture.update(blackSquare, i*size / 8, j*size / 8);
		};
	};

	m_sprite.setTexture(m_boardTexture);

	if (!m_font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf")) {
		std::cout << "failed to load font" << std::endl;
	}
	m_text.setFont(m_font);
	m_text.setString(m_printMoves);
	m_text.setFillColor(sf::Color::White);
	m_text.setPosition(800.f, 0.f);

	if (!pawnTexture.loadFromFile("pawn.png"))
		std::cout << "failed to load pawn texture" << std::endl;
	for (int i = 0; i < 8; i++) {//create pawns on the board
		m_squares[8 + i] = new Pawn(100, i, 1, 1, m_pawnTexture, this);
		std::cout << "white pawn " << i << " created at (" << i << ", " << 1 << ")" << std::endl;
		m_squares[48 + i] = new Pawn(100, i, 6, -1, m_pawnTexture, this);
	};
	if (!knightTexture.loadFromFile("knight.png"))
		std::cout << "failed to load knight texture" << std::endl;
	if (!bishopTexture.loadFromFile("bishop.png"))
		std::cout << "failed to load bishop texture" << std::endl;
	if (!rookTexture.loadFromFile("rook.png"))
		std::cout << "failed to load rook texture" << std::endl;
	for (int i = 0; i < 2; i++) {
		//knights
		m_squares[1 + i * 5] = new Knight(100, 1 + 5 * i, 0, 1, m_knightTexture, this);
		std::cout << "white knight " << i << " created at (" << (1 + 5 * i) << ", " << 0 << ")" << std::endl;
		m_squares[57 + i * 5] = new Knight(100, 1 + 5 * i, 7, -1, m_knightTexture, this);
		//bishops
		m_squares[2 + i * 3] = new Bishop(100, 2 + 3 * i, 0, 1, m_bishopTexture, this);
		m_squares[58 + i * 3] = new Bishop(100, 2 + 3 * i, 7, -1, m_bishopTexture, this);
		//rooks
		m_squares[7 * i] = new Rook(100, 7 * i, 0, 1, m_rookTexture, this);
		m_squares[56 + 7 * i] = new Rook(100, 7 * i, 7, -1, m_rookTexture, this);
		std::cout << "black rook " << i << " created at (" << (7 * i) << ", " << 7 << ")" << std::endl;
	};
	if (!queenTexture.loadFromFile("queen.png"))
		std::cout << "failed to load pawn texture" << std::endl;
	if (!kingTexture.loadFromFile("king.png"))
		std::cout << "failed to load pawn texture" << std::endl;
	for (int i = 0; i < 1; i++) {
		//queens
		m_squares[3] = new Queen(100, 3, 0, 1, m_queenTexture, this);
		m_squares[59] = new Queen(100, 3, 7, -1, m_queenTexture, this);
		//kings
		m_whiteKingPos = { 4, 0 };
		m_blackKingPos = { 4, 7 };
		m_squares[4] = new King(100, 4, 0, 1, m_kingTexture, this);
		m_squares[60] = new King(100, 4, 7, -1, m_kingTexture, this);
	};

	for (int i = 0; i < 32; i++) {//fill the rest of the board with empty squares
		m_squares[16 + i] = new EmptySquare(100, i % 8, 2 + i / 8, 0, m_kingTexture, this);
	};
};

Board::Board(int size, std::array<Piece*, 64> squares, std::array<int, 2> whiteKingPos, std::array<int, 2> blackKingPos) {
	//size should be a multiple of 8, not sure how it will draw otherwise
	sf::Image blackSquare;
	blackSquare.create(size / 8, size / 8, sf::Color::Black);
	sf::Image whiteSquare;
	whiteSquare.create(size / 8, size / 8, sf::Color::White);

	m_boardTexture.create(size, size);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if ((i + j) % 2 == 0)
				m_boardTexture.update(whiteSquare, i*size / 8, j*size / 8);
			else
				m_boardTexture.update(blackSquare, i*size / 8, j*size / 8);
		};
	};

	m_sprite.setTexture(m_boardTexture);

	m_squares.swap(squares);
	m_whiteKingPos = whiteKingPos;
	m_blackKingPos = blackKingPos;
}
//need destructor defined to clear out objects on heap
Board::~Board() {
	for (int i = 0; i < 64; i++) {
		delete m_squares[i];
	};
};

//-------maybe put above in constructor? no need to create a texture every time this is drawn--------
//draw sprite lel
void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
	for (int i = 0; i < 64; i++) {
		target.draw(*m_squares[i], states);
	};
	target.draw(m_text, states);
};
//see above

//note this can't be used with buffer boards
std::vector<Piece*> Board::inCheckCheck() {
	//use undoMove function to revert a move that leaves king in check
	std::vector<Piece*> output;
	for (int i = 0; i < 64; i++) {
		if (m_squares[i]->getColor() == -1 * turn && m_squares[i]->legalMove(turn == 1?m_whiteKingPos:m_blackKingPos, m_buffer)) {
			output.push_back(m_squares[i]);
			std::cout << "checking piece is " << m_squares[i]->getName() << std::endl;
		}
	};
	return output;
};

void Board::move(std::array<int, 2> currentPos, std::array<int, 2> newPos) {
	inSpace(currentPos)->move(newPos);
	delete m_squares[newPos[0] + 8 * newPos[1]];
	m_squares[newPos[0] + 8 * newPos[1]] = m_squares[currentPos[0] + 8 * currentPos[1]];
	m_squares[currentPos[0] + 8 * currentPos[1]] = new EmptySquare(0, currentPos[0], currentPos[1], 0, m_kingTexture, this);
	std::cout << "Piece Moved!" << std::endl;

	if (currentPos == m_whiteKingPos) {
		m_whiteKingPos = newPos;
	}
	else if (currentPos == m_blackKingPos) {
		m_blackKingPos = newPos;
	}

}

void Board::updateMoveList(std::array<int, 2> currentPos, std::array<int, 2> newPos) {
	
}

void Board::movePiece(std::array<int, 2> currentPos, std::array<int, 2> newPos) {
	Piece * ppiece = inSpace(currentPos);
	if (1) {
		//for some reason, as soon as ^this legalMove returns a value, it breaks all the textures in board's m_square array
		//i'll try changing it to take board pointers instead of board objects
		if (ppiece->canCastle(newPos)) {
			m_movelist.push_back({ currentPos, newPos });
			//add undo components
			m_text.setString(m_printMoves.append(movelistToString({ currentPos, newPos }, ppiece, 1, 0)));
			delete m_squares[newPos[0] + 8 * newPos[1]];
			m_squares[newPos[0] + 8 * newPos[1]] = ppiece;
			ppiece->move(newPos);
			m_squares[currentPos[0] + 8 * currentPos[1]] = new EmptySquare(0, currentPos[0], currentPos[1], 0, m_kingTexture, this);
			if (newPos[0] > currentPos[0]) {
				delete m_squares[newPos[0] - 1 + 8 * newPos[1]];
				m_squares[7 + 8 * newPos[1]]->move({5, newPos[1]});
				m_squares[newPos[0] - 1 + 8 * newPos[1]] = m_squares[newPos[0] + 1 + 8 * newPos[1]];
				m_squares[newPos[0] + 1 + 8 * newPos[1]] = new EmptySquare(0, newPos[0] + 1, newPos[1], 0, m_kingTexture, this);
			}
			else {
				delete m_squares[3 + 8 * newPos[1]];
				m_squares[8 * newPos[1]]->move({ 3, newPos[1] });
				m_squares[3 + 8 * newPos[1]] = m_squares[8 * currentPos[1]];
				m_squares[8 * currentPos[1]] = new EmptySquare(0, 0, newPos[1], 0, m_kingTexture, this);
			}
			std::cout << "castled" << std::endl;

			turn = -1 * turn;
		}
		else if (0) { //promotion
			m_movelist.push_back({ currentPos, newPos });
			m_captureList.push_back(inSpace(newPos)->getName());
			m_capturePosList.push_back(newPos);
			//add undo components
			m_text.setString(m_printMoves.append(movelistToString({ currentPos, newPos }, ppiece, 2, (inSpace(newPos)->getColor() == 0) ? 0 : 1)));
			delete m_squares[newPos[0] + 8 * newPos[1]];
			delete m_squares[currentPos[0] + 8 * currentPos[1]];
			//always gives queens atm
			m_squares[newPos[0] + 8 * newPos[1]] = new Queen(100, newPos[0], newPos[1], turn, m_queenTexture, this);
			m_squares[currentPos[0] + 8 * currentPos[1]] = new EmptySquare(0, currentPos[0], currentPos[1], 0, m_kingTexture, this);
			std::cout << "pawn promoted" << std::endl;

			turn = -1 * turn;
		}
		else if (ppiece->canEnPassant(newPos)) {
			m_movelist.push_back({ currentPos, newPos });
			m_captureList.push_back(inSpace(newPos)->getName());
			m_capturePosList.push_back(newPos);
			//add undo components
			m_text.setString(m_printMoves.append(movelistToString({ currentPos, newPos }, ppiece, 3, (inSpace(newPos)->getColor() == 0) ? 0 : 1)));
			ppiece->move(newPos);
			delete m_squares[newPos[0] + 8 * (newPos[1] - turn)];
			m_squares[newPos[0] + 8 * (newPos[1] - 1)] = new EmptySquare(0, newPos[0], newPos[1] - turn, 0, m_kingTexture, this);
			delete m_squares[newPos[0] + 8 * newPos[1]];
			m_squares[newPos[0] + 8 * newPos[1]] = m_squares[currentPos[0] + 8*currentPos[1]];
			m_squares[currentPos[0] + 8 * currentPos[1]] = new EmptySquare(0, currentPos[0], currentPos[1], 0, m_kingTexture, this);
			std::cout << "en passant" << std::endl;

			turn = -1 * turn;
		}
		else {
			m_movelist.push_back({ currentPos, newPos });
			m_captureList.push_back(inSpace(newPos)->getName());
			m_capturePosList.push_back(newPos);
			m_text.setString(m_printMoves.append(movelistToString({ currentPos, newPos }, ppiece, 0, (inSpace(newPos)->getColor() == 0) ? 0 : 1)));
			ppiece->move(newPos);
			delete m_squares[newPos[0] + 8 * newPos[1]];
			m_squares[newPos[0] + 8 * newPos[1]] = m_squares[currentPos[0] + 8 * currentPos[1]];
			m_squares[currentPos[0] + 8 * currentPos[1]] = new EmptySquare(0, currentPos[0], currentPos[1], 0, m_kingTexture, this);
			std::cout << "Piece Moved!" << std::endl;

			if (currentPos == m_whiteKingPos) {
				m_whiteKingPos = newPos;
			}
			else if (currentPos == m_blackKingPos) {
				m_blackKingPos = newPos;
			}
			turn = -1 * turn;

			if (m_buffer != NULL) {
				std::vector<Piece*> checkingPieces = coveredSquare((turn == 1) ? m_whiteKingPos : m_blackKingPos, -1*turn);
				if (checkingPieces.size() != 0) {
					std::cout << "check" << std::endl;
					if (checkmateCheck((turn == 1) ? m_whiteKingPos : m_blackKingPos, checkingPieces))
						std::cout << "Checkmate!" << std::endl;
				}
			}
		}
	}
	else {
		std::cout << "Invalid Move!" << std::endl;
	};
};

//note this function can't be used with a buffer board itself
void Board::validMove(std::array<int, 2> currentPos, std::array<int, 2> newPos) {
	if (inSpace(currentPos)->getColor() == turn && inSpace(currentPos)->legalMove(newPos, m_buffer)) {
		movePiece(currentPos, newPos);
		m_buffer->movePiece(currentPos, newPos);
	}
	else {
		std::cout << "invalid move" << std::endl;
	}
}

Piece * Board::recreatePiece(int file, int rank, int color, std::string identifier) {
	if (identifier == "") {
		Piece * ppiece = new Pawn(100, file, rank, color, m_pawnTexture, this);
		return ppiece;
	}
	else if (identifier == "N") {
		Piece * ppiece = new Knight(100, file, rank, color, m_knightTexture, this);
		return ppiece;
	}
	else if (identifier == "B") {
		Piece * ppiece = new Bishop(100, file, rank, color, m_bishopTexture, this);
		return ppiece;
	}
	else if (identifier == "R") {
		Piece * ppiece = new Rook(100, file, rank, color, m_rookTexture, this);
		return ppiece;
	}
	else if (identifier == "Q") {
		Piece * ppiece = new Queen(100, file, rank, color, m_queenTexture, this);
		return ppiece;
	}
	else if (identifier == "K") {
		Piece * ppiece = new King(100, file, rank, color, m_kingTexture, this);
		return ppiece;
	}
	else if (identifier == "S") {
		Piece * ppiece = new EmptySquare(0, file, rank, color, m_kingTexture, this);
		return ppiece;
	}
	else {
		std::cout << "error creating piece with recreatepiece(), please exit to ensure no memory leakage" << std::endl;
	}
}

void Board::undoMove() {
	//capturePosList may not be needed if undo can distinguish between special moves
	delete m_squares[m_movelist.back()[0][0] + 8 * m_movelist.back()[0][1]]; //delete square last move was made from
	m_squares[m_movelist.back()[1][0] + 8 * m_movelist.back()[1][1]]->move(m_movelist.back()[0]); //change piece position to its old one
	m_squares[m_movelist.back()[0][0] + 8 * m_movelist.back()[0][1]] = m_squares[m_movelist.back()[1][0] + 8 * m_movelist.back()[1][1]]; //move the pieces pointer back to the old square
	m_squares[m_movelist.back()[1][0] + 8 * m_movelist.back()[1][1]] = recreatePiece(m_capturePosList.back()[0], m_capturePosList.back()[1], turn, m_captureList.back()); //remake the piece that was captured beforehand

	if (inSpace(m_movelist.back()[0])->getName() == "K") {
		if (inSpace(m_movelist.back()[0])->getColor() == 1) {
			m_whiteKingPos = m_movelist.back()[0];
		}
		else {
			m_blackKingPos = m_movelist.back()[0];
		}
	}

	m_movelist.pop_back();
	m_captureList.pop_back();
	m_capturePosList.pop_back();

	turn = -1 * turn;
	
	std::size_t found = m_printMoves.find_last_of("-\n");
	m_printMoves.erase(found, m_printMoves.length() - found);
	m_text.setString(m_printMoves);
};

Piece* Board::inSpace(std::array<int, 2> position) {
	return m_squares[position[0] + 8 * position[1]];
};

std::array<std::array<int, 2>, 2> Board::previousMove() {
	return (m_movelist.size() == 0) ? (std::array<std::array<int, 2>, 2> { std::array<int, 2> {0, 0}, std::array<int, 2> {0, 0}}) : (m_movelist.back());
};

std::string Board::movelistToString(std::array<std::array<int, 2>, 2> move, Piece * piece, int specialMove, bool capture) {
	std::string output;

	if (piece->getColor() == 1)
		output = "\n";
	else
		output = "-";

	if (!specialMove) {

		if (capture) {
			if (piece->getName() == "")
				output.append(gridNotation(move[0]).substr(0, 1));
			else
				output.append(piece->getName());

			output.append("x");
		}
		else {
			output.append(piece->getName());
		}
		output.append(gridToNotate(move[1], specialMove));
		return output;
	}
	else if (specialMove == 1) {
		//castle--------------------------------------------------------------
		output.append(gridToNotate(move[1], specialMove));
		return output;
	}
	else if (specialMove == 2) {
		//promotion------------------------------------------------------------
		if (capture)
			output.append(gridNotation(move[0]).substr(0, 1) + "x");

		output.append(gridToNotate(move[1], specialMove));
		return output;
	}
	else if (specialMove == 3) {
		//en passant-----------------------------------------------------------
		output.append(gridNotation(move[0]).substr(0, 1));
		output.append("x");
		output.append(gridToNotate(move[1], specialMove));
		
		return output;
	}
};

std::string Board::gridToNotate(std::array<int, 2> grid, int specialMove) {
	std::string output;
	if (!specialMove) {
		output.append(gridNotation(grid));
		return output;
	}
	else if (specialMove == 1) {
		//castle
		if (grid[0] == 6) {
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
		output.append(gridNotation(grid));
		output.append(" e.p.");
		return output;
	}
};

std::string Board::gridNotation(std::array<int, 2> grid) {
	std::string output;

	switch (grid[0]) {
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
	output.append(std::to_string(grid[1] + 1));
	return output;
}

std::array<int, 2> Board::kingPosition(int color) {
	if (color == 1)
		return m_whiteKingPos;
	else
		return m_blackKingPos;
};

std::vector<Piece*> Board::coveredSquare(std::array<int, 2> testPos, int color) {
	int posX = 7 - testPos[0];
	int negX = testPos[0];
	int posY = 7 - testPos[1];
	int negY = testPos[1];

	std::vector<Piece*> output;
//check diagonals
	for (int i = 1; i <= std::min(posX, posY); i++) {
		if (inSpace({ negX + i, negY + i })->getColor() == 0)
			continue;
		else if (inSpace({ negX + i, negY + i })->getColor() == color && (inSpace({ negX + i, negY + i })->getName() == "B" || inSpace({ negX + i, negY + i })->getName() == "Q")) {
			output.push_back(inSpace({ negX + i, negY + i }));
			std::cout << "off color piece in top right diagonal " << negX + i << negY + i << std::endl;
			break;
		}
		else
			break;
	}
	for (int i = 1; i <= std::min(negX, posY); i++) {
		if (inSpace({ negX - i, negY + i })->getColor() == 0)
			continue;
		else if (inSpace({ negX - i, negY + i })->getColor() == color && (inSpace({ negX - i, negY + i })->getName() == "B" || inSpace({ negX - i, negY + i })->getName() == "Q")) {
			output.push_back(inSpace({ negX - i, negY + i }));
			std::cout << "off color piece in top left diagonal" << std::endl;
			break;
		}
		else
			break;
	}
	for (int i = 1; i <= std::min(negX, negY); i++) {
		if (inSpace({ negX - i, negY - i })->getColor() == 0)
			continue;
		else if (inSpace({ negX - i, negY - i })->getColor() == color && (inSpace({ negX - i, negY - i })->getName() == "B" || inSpace({ negX - i, negY - i })->getName() == "Q")) {
			output.push_back(inSpace({ negX - i, negY - i }));
			std::cout << "off color piece in bottom left diagonal" << std::endl;
			break;
		}
		else
			break;
	}
	for (int i = 1; i <= std::min(posX, negY); i++) {
		if (inSpace({ negX + i, negY - i })->getColor() == 0)
			continue;
		else if (inSpace({ negX + i, negY - i })->getColor() == color && (inSpace({ negX + i, negY - i })->getName() == "B" || inSpace({ negX + i, negY - i })->getName() == "Q")) {
			output.push_back(inSpace({ negX + i, negY - i }));
			std::cout << "off color piece in bottom right diagonal" << std::endl;
			break;
		}
		else
			break;
	}
	
//check horizontals
	for (int i = 1; i <= posX; i++) {
		if (inSpace({ negX + i, negY})->getColor() == 0)
			continue;
		else if (inSpace({ negX + i, negY })->getColor() == color && (inSpace({ negX + i, negY })->getName() == "R" || inSpace({ negX + i, negY })->getName() == "Q")) {
			output.push_back(inSpace({ negX + i, negY}));
			std::cout << "off color piece in right horizontal" << std::endl;
			break;
		}
		else
			break;
	}
	for (int i = 1; i <= posY; i++) {
		if (inSpace({ negX, negY + i })->getColor() == 0)
			continue;
		else if (inSpace({ negX, negY + i })->getColor() == color && (inSpace({ negX, negY + i })->getName() == "R" || inSpace({ negX, negY + i })->getName() == "Q")) {
			output.push_back(inSpace({ negX, negY + i }));
			std::cout << "off color piece in top horizontal" << negX << negY + i << std::endl;
			break;
		}
		else
			break;
	}
	for (int i = 1; i <= negX; i++) {
		if (inSpace({ negX - i, negY})->getColor() == 0)
			continue;
		else if (inSpace({ negX - i, negY })->getColor() == color && (inSpace({ negX - i, negY })->getName() == "R" || inSpace({ negX - i, negY })->getName() == "Q")) {
			output.push_back(inSpace({ negX - i, negY}));
			std::cout << "off color piece in left horizontal" << std::endl;
			break;
		}
		else
			break;
	}
	for (int i = 1; i <= negY; i++) {
		if (inSpace({ negX , negY - i })->getColor() == 0)
			continue;
		else if (inSpace({ negX , negY - i })->getColor() == color && (inSpace({ negX , negY - i })->getName() == "R" || inSpace({ negX , negY - i })->getName() == "Q")) {
			output.push_back(inSpace({ negX, negY - i }));
			std::cout << "off color piece in bottom horizontal" << std::endl;
			break;
		}
		else
			break;
	}
	
//check knights
	for (int i = 1; i < 12; i++) {
		if (i % 3 != 0) {
			int testX = (int)(negX + 2.23607*cos(i*3.1415926 / 6.0) + 0.5);
			int testY = (int)(negY + 2.23607*sin(i*3.1415926 / 6.0) + 0.5);
			if ((testX < 8 && testX>=0) && (testY < 8 && testY>=0)) {
				if (inSpace({ testX, testY })->getColor() == color && inSpace({ testX, testY })->getName() == "N") {
					output.push_back(inSpace({ testX, testY }));
					break;
				}
			}
		}
	}
	
//check pawns (maybe wrap into diagonals?)

	return output;
};

//note this function can't be used with a buffer board itself
bool Board::checkmateCheck(std::array<int, 2> kingPos, std::vector<Piece*> checkingPieces) {
	//three ways to get out of check
	//note: this function assumes we're testing the current players turn to see if they are in checkmate
	//1. move the king
	for (int i = -1; i < 2; i++) {
		for (int j = -1; j < 2; j++) {
			if (i || j) {
				int testX = kingPos[0] + i;
				int testY = kingPos[1] + j;
				if ((testX >= 0 && testX <= 7) && (testY >= 0 && testY <= 7)) {

					if (inSpace(kingPos)->legalMove({ testX, testY }, m_buffer)) {

						if (coveredSquare({ testX, testY }, -1*turn).size() != 0)

							return false;
					}
				}
			}
		}
	}
	std::cout << "no available king moves" << std::endl;
	//2. capture the checking piece
	if (checkingPieces.size() == 1) {
		for (int i = 0; i < 64; i++) {
			if (m_squares[i]->getColor() == turn && m_squares[i]->legalMove(checkingPieces[0]->getPosition(), m_buffer))
				return false;
		}
	}
	std::cout << "unable to capture checking piece" << std::endl;
	//3. move in between the checking piece and the king
	if (checkingPieces.size() == 1) {
		if ((checkingPieces[0]->getName() != "N") && (checkingPieces[0]->getName() != "")) {
			std::array<int, 2> checkingPiecePos = checkingPieces[0]->getPosition();
			if (checkingPiecePos[0] == kingPos[0]) {
				std::cout << "checking file" << std::endl;
				int diff = abs(checkingPiecePos[1] - kingPos[1]);
				if (diff > 1) {
					int sign = (checkingPiecePos[1] - kingPos[1]) / diff;
					for (int i = 1; i < diff; i++) {
						if (m_squares[i]->getColor() == turn && m_squares[i]->legalMove({ checkingPiecePos[0], checkingPiecePos[1] + i*sign }, m_buffer))
							return false;
					}
				}
			} else if (checkingPiecePos[1] == kingPos[1]) {
				std::cout << "checking rank" << std::endl;
				int diff = abs(checkingPiecePos[0] - kingPos[0]);
				if (diff > 1) {
					int sign = (checkingPiecePos[0] - kingPos[0]) / diff;
					for (int i = 1; i < diff; i++) {
						if (m_squares[i]->getColor() == turn && m_squares[i]->legalMove({ checkingPiecePos[0] + i*sign, checkingPiecePos[1]}, m_buffer))
							return false;
					}
				}
			} else {
				std::cout << "checking diag" << std::endl;
				int diff = abs(checkingPiecePos[1] - kingPos[1]);
				if (diff > 1) {
					int signX = (checkingPiecePos[0] - kingPos[0]) / diff;
					int signY = (checkingPiecePos[1] - kingPos[1]) / diff;
					for (int i = 1; i < diff; i++) {
						if (m_squares[i]->getColor() == turn && m_squares[i]->legalMove({ checkingPiecePos[0] + i*signX, checkingPiecePos[1] + i*signY }, m_buffer))
							return false;
					}
				}
			}
		}
	}
	std::cout << "unable to block checking piece" << std::endl;
	return true;
};