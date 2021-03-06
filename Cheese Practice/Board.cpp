
#include "Board.h"
#include "real pieces.h"
#include "Movelist.h"

//buffer board constructor
Board::Board() {
	m_movelist = new Movelist(this);

	for (int i = 0; i < 8; i++) {//create pawns on the board
		m_squares[8 + i] = new Pawn(0, i, 1, 1, &pawnTexture, this);

		m_squares[48 + i] = new Pawn(0, i, 6, -1, &pawnTexture, this);
	};
	for (int i = 0; i < 2; i++) {
		//knights
		m_squares[1 + i * 5] = new Knight(0, 1 + 5 * i, 0, 1, &knightTexture, this);

		m_squares[57 + i * 5] = new Knight(0, 1 + 5 * i, 7, -1, &knightTexture, this);
		//bishops
		m_squares[2 + i * 3] = new Bishop(0, 2 + 3 * i, 0, 1, &bishopTexture, this);

		m_squares[58 + i * 3] = new Bishop(0, 2 + 3 * i, 7, -1, &bishopTexture, this);
		//rooks
		m_squares[7 * i] = new Rook(0, 7 * i, 0, 1, &rookTexture, this);

		m_squares[56 + 7 * i] = new Rook(0, 7 * i, 7, -1, &rookTexture, this);
	};
	//queens
	m_squares[3] = new Queen(0, 3, 0, 1, &queenTexture, this);

	m_squares[59] = new Queen(0, 3, 7, -1, &queenTexture, this);
	//kings
	m_whiteKingPos = { 4, 0 };
	m_blackKingPos = { 4, 7 };
	m_squares[4] = new King(0, 4, 0, 1, &kingTexture, this);

	m_squares[60] = new King(0, 4, 7, -1, &kingTexture, this);

	for (int i = 0; i < 32; i++) {//fill the rest of the board with empty squares
		m_squares[16 + i] = new EmptySquare(100, i % 8, 2 + i / 8, 0, &kingTexture, this);
	};
};

Board::Board(int size, StateManager * stateManager) {
	//size should be a multiple of 8, not sure how it will draw otherwise
	m_buffer = new Board();

	m_stateManager = stateManager;

	m_movelist = new Movelist(this);

	m_whitePieces.reserve(16);
	m_blackPieces.reserve(16);

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
	
	//eventually here you should be able to create the board anywhere on the window, not just the top left
	m_xPos = 0;
	m_yPos = 0;
	m_size = size;
	m_sprite.setTexture(m_boardTexture);

	if (!pawnTexture.loadFromFile("pawn.png"))
		std::cout << "failed to load pawn texture" << std::endl;

	for (int i = 0; i < 8; i++) {
		//create pawns on the board
		m_squares[8 + i] = new Pawn(100, i, 1, 1, &pawnTexture, this);
		m_whitePieces.push_back(m_squares[8 + i]);

		m_squares[48 + i] = new Pawn(100, i, 6, -1, &pawnTexture, this);
		m_blackPieces.push_back(m_squares[48 + i]);
	};
	if (!knightTexture.loadFromFile("knight.png"))
		std::cout << "failed to load knight texture" << std::endl;
	if (!bishopTexture.loadFromFile("bishop.png"))
		std::cout << "failed to load bishop texture" << std::endl;
	if (!rookTexture.loadFromFile("rook.png"))
		std::cout << "failed to load rook texture" << std::endl;

	for (int i = 0; i < 2; i++) {
		//knights
		m_squares[1 + i * 5] = new Knight(100, 1 + 5 * i, 0, 1, &knightTexture, this);
		m_whitePieces.push_back(m_squares[1 + i * 5]);

		m_squares[57 + i * 5] = new Knight(100, 1 + 5 * i, 7, -1, &knightTexture, this);
		m_blackPieces.push_back(m_squares[57 + i * 5]);
		//bishops
		m_squares[2 + i * 3] = new Bishop(100, 2 + 3 * i, 0, 1, &bishopTexture, this);
		m_whitePieces.push_back(m_squares[2 + i * 3]);

		m_squares[58 + i * 3] = new Bishop(100, 2 + 3 * i, 7, -1, &bishopTexture, this);
		m_blackPieces.push_back(m_squares[58 + i * 3]);
		//rooks
		m_squares[7 * i] = new Rook(100, 7 * i, 0, 1, &rookTexture, this);
		m_whitePieces.push_back(m_squares[7 * i]);

		m_squares[56 + 7 * i] = new Rook(100, 7 * i, 7, -1, &rookTexture, this);
		m_blackPieces.push_back(m_squares[56 + 7 * i]);
	};
	if (!queenTexture.loadFromFile("queen.png"))
		std::cout << "failed to load pawn texture" << std::endl;
	if (!kingTexture.loadFromFile("king.png"))
		std::cout << "failed to load pawn texture" << std::endl;

	if (!m_MMbuttonTexture.loadFromFile("mainMenuButton.png"))
		std::cout << "failed to load button texture" << std::endl;

	if (!m_RestartButtonTexture.loadFromFile("restartbutton.png"))
		std::cout << "failed to load restart texture" << std::endl;

	m_RestartButtonSprite.setTexture(m_RestartButtonTexture);
	m_RestartButtonSprite.setPosition(sf::Vector2f(200.f, 800.f));
	m_MMbuttonSprite.setTexture(m_MMbuttonTexture);
	m_MMbuttonSprite.setPosition(sf::Vector2f(0.f, 800.f));

	//queens
	m_squares[3] = new Queen(100, 3, 0, 1, &queenTexture, this);
	m_whitePieces.push_back(m_squares[3]);

	m_squares[59] = new Queen(100, 3, 7, -1, &queenTexture, this);
	m_blackPieces.push_back(m_squares[59]);
	//kings
	m_whiteKingPos = { 4, 0 };
	m_blackKingPos = { 4, 7 };
	m_squares[4] = new King(100, 4, 0, 1, &kingTexture, this);
	m_whitePieces.push_back(m_squares[4]);

	m_squares[60] = new King(100, 4, 7, -1, &kingTexture, this);
	m_blackPieces.push_back(m_squares[60]);

	for (int i = 0; i < 32; i++) {//fill the rest of the board with empty squares
		m_squares[16 + i] = new EmptySquare(100, i % 8, 2 + i / 8, 0, &kingTexture, this);
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
	delete m_movelist;
	if (m_buffer) {
		delete m_buffer;
	};
};

void Board::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite, states);
	for (int i = 0; i < 64; i++) {
		target.draw(*m_squares[i], states);
	};
	target.draw(*m_movelist, states);
	target.draw(m_MMbuttonSprite, states);
	target.draw(m_RestartButtonSprite, states);
};

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

//moves piece without checking legality
void Board::move(std::array<int, 2> currentPos, std::array<int, 2> newPos) {
	inSpace(currentPos)->move(newPos);
	delete m_squares[newPos[0] + 8 * newPos[1]];
	m_squares[newPos[0] + 8 * newPos[1]] = m_squares[currentPos[0] + 8 * currentPos[1]];
	m_squares[currentPos[0] + 8 * currentPos[1]] = new EmptySquare(0, currentPos[0], currentPos[1], 0, &kingTexture, this);
	std::cout << "Piece Moved!" << std::endl;

	if (currentPos == m_whiteKingPos) {
		m_whiteKingPos = newPos;
	}
	else if (currentPos == m_blackKingPos) {
		m_blackKingPos = newPos;
	}

}

//checks legality before moving piece
void Board::movePiece(std::array<int, 2> currentPos, std::array<int, 2> newPos) {
	Piece * ppiece = inSpace(currentPos);
	if ((!(inSpace(newPos)->getColor())) || !(ppiece->getName() == "")) {
		m_drawCounter++;
		m_drawCountOnTurn.push_back(m_drawCounter);
	}
	else {
		m_drawCounter = 0;
		m_drawCountOnTurn.push_back(m_drawCounter);
	}
	if (1) {
		if (ppiece->canCastle(newPos)) {
			m_movelist->addToMovelist(currentPos, newPos);
			m_squares[newPos[0] + 8 * newPos[1]] = ppiece;
			ppiece->move(newPos);
			m_squares[currentPos[0] + 8 * currentPos[1]] = new EmptySquare(0, currentPos[0], currentPos[1], 0, &kingTexture, this);
			if (newPos[0] > currentPos[0]) {
				delete m_squares[newPos[0] - 1 + 8 * newPos[1]];
				m_squares[7 + 8 * newPos[1]]->move({5, newPos[1]});
				m_squares[newPos[0] - 1 + 8 * newPos[1]] = m_squares[newPos[0] + 1 + 8 * newPos[1]];
				m_squares[newPos[0] + 1 + 8 * newPos[1]] = new EmptySquare(0, newPos[0] + 1, newPos[1], 0, &kingTexture, this);
			}
			else {
				delete m_squares[3 + 8 * newPos[1]];
				m_squares[8 * newPos[1]]->move({ 3, newPos[1] });
				m_squares[3 + 8 * newPos[1]] = m_squares[8 * currentPos[1]];
				m_squares[8 * currentPos[1]] = new EmptySquare(0, 0, newPos[1], 0, &kingTexture, this);
			}
			std::cout << "castled" << std::endl;

			turn = -1 * turn;
		}
		else if (ppiece->canPromote(newPos)) { //promotion
			m_movelist->addToMovelist(currentPos, newPos);
			delete m_squares[currentPos[0] + 8 * currentPos[1]];
			//always gives queens atm
			m_squares[newPos[0] + 8 * newPos[1]] = new Queen(100, newPos[0], newPos[1], turn, &queenTexture, this);
			(turn == 1) ? m_whitePieces.push_back(m_squares[newPos[0] + 8 * newPos[1]]) : m_blackPieces.push_back(m_squares[newPos[0] + 8 * newPos[1]]);
			m_squares[currentPos[0] + 8 * currentPos[1]] = new EmptySquare(0, currentPos[0], currentPos[1], 0, &kingTexture, this);
			std::cout << "pawn promoted" << std::endl;

			turn = -1 * turn;
		}
		else if (ppiece->canEnPassant(newPos)) {
			//deleting piece being added to capturelist, fix it
			m_movelist->addToMovelist(currentPos, newPos);
			ppiece->move(newPos);
			m_squares[newPos[0] + 8 * currentPos[1]] = new EmptySquare(0, newPos[0], currentPos[1], 0, &kingTexture, this);
			delete m_squares[newPos[0] + 8 * newPos[1]];
			m_squares[newPos[0] + 8 * newPos[1]] = m_squares[currentPos[0] + 8*currentPos[1]];
			m_squares[currentPos[0] + 8 * currentPos[1]] = new EmptySquare(0, currentPos[0], currentPos[1], 0, &kingTexture, this);
			std::cout << "en passant" << std::endl;

			turn = -1 * turn;
		}
		else {
			m_movelist->addToMovelist(currentPos, newPos);
			ppiece->move(newPos);
			m_squares[newPos[0] + 8 * newPos[1]] = m_squares[currentPos[0] + 8 * currentPos[1]];
			m_squares[currentPos[0] + 8 * currentPos[1]] = new EmptySquare(0, currentPos[0], currentPos[1], 0, &kingTexture, this);
			std::cout << "Piece Moved!" << std::endl;

			if (currentPos == m_whiteKingPos) {
				m_whiteKingPos = newPos;
			}
			else if (currentPos == m_blackKingPos) {
				m_blackKingPos = newPos;
			}
			turn = -1 * turn;
		}

		if (m_buffer != NULL) {
			std::vector<Piece*> checkingPieces = coveredSquare((turn == 1) ? m_whiteKingPos : m_blackKingPos, -1 * turn);
			if (checkingPieces.size() != 0) {
				std::cout << "check" << std::endl;
				if (checkmateCheck((turn == 1) ? m_whiteKingPos : m_blackKingPos, checkingPieces))
					std::cout << "Checkmate!" << std::endl;
			}
			else {
				if (stalemateCheck())
					std::cout << "Stalemate!" << std::endl;
			}

			if (m_drawCounter >= 50) {
				std::cout << "Claim 50-move rule draw?" << std::endl;
			}
			std::string boardHash = m_movelist->hashBoard();
			if (!(m_movelist->m_boardStateMap.count(boardHash)))
				m_movelist->m_boardStateMap[boardHash] = 1;
			else {
				m_movelist->m_boardStateMap[boardHash]++;
				if (m_movelist->m_boardStateMap[boardHash] >= 3)
					std::cout << "Draw by repetition" << std::endl;
			}
			if (insufficientMaterial())
				std::cout << "Draw by insufficient material" << std::endl;
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

void Board::undoMove() {
	m_drawCounter = m_drawCountOnTurn.back();
	m_drawCountOnTurn.pop_back();
	
	std::array<std::array<int, 2>, 2> lastMove = m_movelist->previousMove();

	delete m_squares[lastMove[0][0] + 8 * lastMove[0][1]]; //delete square last move was made from
	m_squares[lastMove[1][0] + 8 * lastMove[1][1]]->move(lastMove[0]); //change piece position to its old one
	m_squares[lastMove[0][0] + 8 * lastMove[0][1]] = m_squares[lastMove[1][0] + 8 * lastMove[1][1]]; //move the pieces pointer back to the old square

	if (m_movelist->m_moveType.back() == ChessMoves::NORMAL) {// normal move
		m_squares[lastMove[1][0] + 8 * lastMove[1][1]] = m_movelist->m_captureList.back();
	}
	else if (m_movelist->m_moveType.back() == ChessMoves::CASTLE) {//castling
		m_squares[lastMove[1][0] + 8 * lastMove[1][1]] = m_movelist->m_captureList.back();

		if (lastMove[1][0] == 6) {
			delete m_squares[7 + 8 * lastMove[1][1]];
			m_squares[5 + 8 * lastMove[1][1]]->move({7, lastMove[1][1]});
			m_squares[7 + 8 * lastMove[1][1]] = m_squares[5 + 8 * lastMove[1][1]];
			m_squares[5 + 8 * lastMove[1][1]] = new EmptySquare(0, 5, lastMove[1][1], 0, &kingTexture, this);
		}
		else {
			delete m_squares[8 * lastMove[1][1]];
			m_squares[3 + 8 * lastMove[1][1]]->move({ 0, lastMove[1][1] });
			m_squares[8 * lastMove[1][1]] = m_squares[3 + 8 * lastMove[1][1]];
			m_squares[3 + 8 * lastMove[1][1]] = new EmptySquare(0, 3, lastMove[1][1], 0, &kingTexture, this);
		}
	}
	else if (m_movelist->m_moveType.back() == ChessMoves::PROMOTION) {//promotion
		m_squares[lastMove[1][0] + 8 * lastMove[1][1]] = m_movelist->m_captureList.back();
		delete m_squares[lastMove[0][0] + 8 * lastMove[0][1]];
		(turn == 1) ? m_blackPieces.pop_back() : m_whitePieces.pop_back();
		m_squares[lastMove[0][0] + 8 * lastMove[0][1]] = new Pawn(100, lastMove[0][0], lastMove[0][1], -1*turn, &pawnTexture, this);
	}
	else {//en passant
		m_squares[lastMove[1][0] + 8 * lastMove[1][1]] = new EmptySquare(0, lastMove[1][0], lastMove[1][1], 0, &kingTexture, this);
		delete m_squares[lastMove[1][0] + 8 * lastMove[0][1]];
		m_squares[lastMove[1][0] + 8 * lastMove[0][1]] = m_movelist->m_captureList.back();
	}

	if (inSpace(lastMove[0])->getName() == "K") {
		if (inSpace(lastMove[0])->getColor() == 1) {
			m_whiteKingPos = lastMove[0];
		}
		else {
			m_blackKingPos = lastMove[0];
		}
	}
	m_movelist->m_captureList.back()->setCapture(0);

	m_movelist->removeFromMovelist();

	turn = -1 * turn;
};

Piece* Board::inSpace(std::array<int, 2> position) {
	return m_squares[position[0] + 8 * position[1]];
};

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

						if (coveredSquare({ testX, testY }, -1 * turn).size() == 0) {

							std::cout << "King can move to x: " << testX << " y: " << testY << std::endl;
							return false;
						}
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
						for (int j = 0; j < 64; j++) {
							if (m_squares[i]->getColor() == turn && m_squares[i]->legalMove({ checkingPiecePos[0], checkingPiecePos[1] + i*sign }, m_buffer))
								return false;
						}
					}
				}
			} else if (checkingPiecePos[1] == kingPos[1]) {
				std::cout << "checking rank" << std::endl;
				int diff = abs(checkingPiecePos[0] - kingPos[0]);
				if (diff > 1) {
					int sign = (checkingPiecePos[0] - kingPos[0]) / diff;
					for (int i = 1; i < diff; i++) {
						for (int j = 0; j < 64; j++) {
							if (m_squares[j]->getColor() == turn && m_squares[j]->legalMove({ checkingPiecePos[0] + i*sign, checkingPiecePos[1] }, m_buffer))
								return false;
						}
					}
				}
			} else {
				std::cout << "checking diag" << std::endl;
				int diff = abs(checkingPiecePos[1] - kingPos[1]);
				if (diff > 1) {
					int signX = (checkingPiecePos[0] - kingPos[0]) / diff;
					int signY = (checkingPiecePos[1] - kingPos[1]) / diff;
					for (int i = 1; i < diff; i++) {
						for (int j = 0; j < 64; j++) {
							if (m_squares[j]->getColor() == turn  && m_squares[j]->getName() != "K" && m_squares[j]->legalMove({ kingPos[0] + i*signX, kingPos[1] + i*signY }, m_buffer)) {
								std::cout << "Square x:" << kingPos[0] + i*signX << " y:" << kingPos[1] + i*signY << " can be moved to with piece " << j << std::endl;
								return false;
							}
						}
					}
				}
			}
		}
	}
	std::cout << "unable to block checking piece" << std::endl;
	return true;
};

bool Board::stalemateCheck() {
	for (int i = 0; i < 64; i++) {
		if (m_squares[i]->getColor() == turn) {
			if (m_squares[i]->listLegalMoves(m_buffer).size())
				return false;
		}
	}
	return true;
};

std::array<std::array<int, 2>, 2> Board::previousMove() {
	return m_movelist->previousMove();
}

void Board::writeMovelistToFile(std::string filename) {
	std::ofstream file(filename, std::ofstream::app);
	if (file.is_open())
		std::cout << "file opened successfully" << std::endl;
	file << m_movelist->m_printMoves << "\n";
	file.close();
}

bool Board::insufficientMaterial() {
	Piece * currentPiece = NULL;
	bool lightB = 0;
	bool darkB = 0;
	bool isKnight = 0;
	for (int i = 0; i < m_whitePieces.size(); i++) {
		currentPiece = m_whitePieces[i];
		if (currentPiece->isCaptured() || currentPiece->getName() == "K") 
			continue;

		if (currentPiece->getName() != "B" && currentPiece->getName() != "N")
			return false;

		if (currentPiece->getName() == "B") {
			if ((currentPiece->getPosition()[0] + currentPiece->getPosition()[1]) % 2 == 0) {
				if (darkB || isKnight)
					return false;
				
				if (!lightB)
					lightB = 1;

				continue;
			}
			else {
				if (lightB || isKnight)
					return false;

				if (!darkB)
					darkB = 1;
				
				continue;
			}
		}
		else {
			if (lightB || darkB || isKnight)
				return false;

			isKnight = 1;
		}
	}
	for (int i = 0; i < m_blackPieces.size(); i++) {
		currentPiece = m_blackPieces[i];
		if (currentPiece->isCaptured() || currentPiece->getName() == "K")
			continue;

		if (currentPiece->getName() != "B" && currentPiece->getName() != "N")
			return false;

		if (currentPiece->getName() == "B") {
			if ((currentPiece->getPosition()[0] + currentPiece->getPosition()[1]) % 2 == 0) {
				if (darkB || isKnight)
					return false;

				continue;
			}
			else {
				if (lightB || isKnight)
					return false;

				continue;
			}
		}
		else {
			if (lightB || darkB || isKnight)
				return false;

			isKnight = 1;
		}
	}
	return true;
}

void Board::flipBoard() {
	for (int i = 0; i < 64; i++) {
		m_squares[i]->flipBoard();
	}
}

//don't forget to change the conditionals to be related to variables instead of arbitrary numbers
//this only cares about release location to choose event, should take click and release into account
void Board::handleEvent(const sf::Event &e) {
	switch (e.type) {

	case sf::Event::MouseButtonPressed:
		if (e.mouseButton.x - m_xPos < m_size && e.mouseButton.y - m_yPos < m_size) {
			m_heldPiece = inSpace({ (e.mouseButton.x - m_xPos) / 100, 7 - (e.mouseButton.y - m_yPos) / 100 });
		}
		else {
		}
		break;

	case sf::Event::MouseButtonReleased:
		if (e.mouseButton.x - m_xPos < m_size && e.mouseButton.y - m_yPos < m_size) {
			std::array<int, 2> movedFrom = m_heldPiece->getPosition();
			std::array<int, 2> movedTo = { (e.mouseButton.x - m_xPos) / 100 , 7 - (e.mouseButton.y - m_yPos) / 100 };
			if (m_heldPiece->legalMove(movedTo, m_buffer)) {
				movePiece(movedFrom,movedTo);
				m_buffer->movePiece(movedFrom, movedTo);
				m_heldPiece->incrementMoves();
			}
		}
		else if(e.mouseButton.x - m_xPos < 200 && e.mouseButton.y - m_yPos < 1000) {
			m_stateManager->switchState(PossibleStates::MENUSTATE1);
		}
		else if (e.mouseButton.x - m_xPos < 400 && e.mouseButton.y - m_yPos < 1000) {
			m_stateManager->restartChess();
		}
		break;

	case sf::Event::MouseMoved:
		if (e.mouseMove.x - m_xPos < m_size && e.mouseMove.y - m_yPos < m_size) {
			//do something
		}
		else {
		}
		break;

	default:
		break;
	}
}