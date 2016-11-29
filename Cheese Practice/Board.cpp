#include <iostream>
#include <array>
#include "Board.h"
#include "real pieces.h"
#include "array conversion therapy.h"


Board::Board(int size) {
	//size should be a multiple of 8, not sure how it will draw otherwise
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

bool Board::inCheckCheck(std::array<int, 2> kingPos) {
	//use undoMove function to revert a move that leaves king in check
	for (int i = 0; i < 64; i++) {
		if (m_squares[i]->getColor() == -1 * turn && m_squares[i]->legalMove(kingPos)) {
			return true;
		}
	};
	return false;
};

void Board::movePiece(std::array<int, 2> currentPos, std::array<int, 2> newPos) {
	Piece * ppiece = this->inSpace(currentPos);
	if (ppiece->getColor() == turn && ppiece->legalMove(newPos) && !(this->inCheckCheck((turn == 1) ?( m_whiteKingPos) : (m_blackKingPos)))) {
		//for some reason, as soon as ^this legalMove returns a value, it breaks all the textures in board's m_square array
		//i'll try changing it to take board pointers instead of board objects
		if (ppiece->canCastle(newPos)) {
			m_movelist.push_back({ currentPos, newPos });
			//add undo components
			m_text.setString(m_printMoves.append(movelistToString({ currentPos, newPos }, this->inSpace(currentPos), 1)));
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
				m_squares[8 * newPos[1]]->move({ 0, newPos[1] });
				m_squares[3 + 8 * newPos[1]] = m_squares[8 * currentPos[1]];
				m_squares[8 * currentPos[1]] = new EmptySquare(0, 0, newPos[1], 0, m_kingTexture, this);
			}
			std::cout << "castled" << std::endl;

			turn = -1 * turn;
		}
		else if (ppiece->canPromote(newPos)) {
			m_movelist.push_back({ currentPos, newPos });
			//add undo components
			m_text.setString(m_printMoves.append(movelistToString({ currentPos, newPos }, this->inSpace(currentPos), 2)));
			delete m_squares[newPos[0] + 8 * newPos[1]];
			delete m_squares[currentPos[0] + 8 * currentPos[1]];
			m_squares[newPos[0] + 8 * newPos[1]] = new Queen(100, newPos[0], newPos[1], turn, m_queenTexture, this);
			m_squares[currentPos[0] + 8 * currentPos[1]] = new EmptySquare(0, currentPos[0], currentPos[1], 0, m_kingTexture, this);
			std::cout << "pawn promoted" << std::endl;

			turn = -1 * turn;
		}
		else if (ppiece->canEnPassant(newPos)) {
			m_movelist.push_back({ currentPos, newPos });
			//add undo components
			m_text.setString(m_printMoves.append(movelistToString({ currentPos, newPos }, this->inSpace(currentPos), 3)));
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
			m_captureList.push_back(this->inSpace(newPos)->getName());
			m_capturePosList.push_back(newPos);
			m_text.setString(m_printMoves.append(movelistToString({ currentPos, newPos }, this->inSpace(currentPos), 0)));
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
		}
	}
	else {
		std::cout << "Invalid Move!" << std::endl;
	};
};

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
	else if (identifier == "S") {
		Piece * ppiece = new EmptySquare(100, file, rank, color, m_kingTexture, this);
		return ppiece;
	}
	else {
		std::cout << "error creating piece with recreatepiece(), please exit to ensure no memory leakage" << std::endl;
	}
}

void Board::undoMove() {
	//capturePosList may not be needed if undo can distinguish special moves
	delete m_squares[m_movelist.back()[0][0] + 8 * m_movelist.back()[0][1]];
	m_squares[m_movelist.back()[0][0] + 8 * m_movelist.back()[0][1]] = m_squares[m_movelist.back()[1][0] + 8 * m_movelist.back()[1][1]];
	m_squares[m_movelist.back()[1][0] + 8 * m_movelist.back()[1][1]] = recreatePiece(m_capturePosList.back()[0], m_capturePosList.back()[1], -1 * turn, m_captureList.back());
	m_movelist.pop_back();
	m_captureList.pop_back();
	m_capturePosList.pop_back();
	turn = -1 * turn;
};

Piece* Board::inSpace(std::array<int, 2> position) {
	return m_squares[position[0] + 8 * position[1]];
};

std::array<std::array<int, 2>, 2> Board::previousMove() {
	return (m_movelist.size() == 0) ? (std::array<std::array<int, 2>, 2> { std::array<int, 2> {0, 0}, std::array<int, 2> {0, 0}}) : (m_movelist.back());
};

