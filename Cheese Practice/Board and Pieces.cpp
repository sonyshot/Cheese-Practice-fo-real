#include <SFML\Graphics.hpp>
#include <iostream>
#include <array>
#include "Board.h"
#include "Piece.h"

class Board : public sf::Drawable {
	sf::Sprite m_sprite;
	std::array<Piece*, 64> m_squares = {};
	std::array<int, 2> m_whiteKingPos;
	std::array<int, 2> m_blackKingPos;
	std::vector<std::array<std::array<int, 2>, 2>> m_movelist;
public:
	//constructor(s) here?
	//this uses 'new' to create piece objects that wont get deleted outside the constructor necessitating 'delete' in the destructor
	Board() {
		for (int i = 0; i < 8; i++) {//create pawns on the board
			m_squares[8 + i] = new Pawn(i, 1, 1);
			m_squares[48 + i] = new Pawn(i, 6, -1);
		};
		for(int i = 0; i < 2; i++){
			//knights
			m_squares[1 + i * 5] = new Knight(1 + 5 * i, 0, 1);
			m_squares[57 + i * 5] = new Knight(1 + 5 * i, 7, -1);
			//bishops
			m_squares[2 + i * 3] = new Bishop(2 + 3 * i, 0, 1);
			m_squares[58 + i * 3] = new Bishop(2 + 3 * i, 7, -1);
			//rooks
			m_squares[7 * i] = new Rook(7 * i, 0, 1);
			m_squares[56 + 7 * i] = new Rook(7 * i, 7, -1);
		};
		for (int i = 0; i < 1; i++) {
			//queens
			m_squares[3] = new Queen(3, 0, 1);
			m_squares[59] = new Queen(3, 7, -1);
			//kings
			m_whiteKingPos = { 4, 0 };
			m_blackKingPos = { 4, 7 };
			m_squares[4] = new King(4, 0, 1);
			m_squares[60] = new King(4, 7, -1);
		};
		
		for (int i = 0; i < 32; i++) {//fill the rest of the board with empty squares
			m_squares[16 + i] = new EmptySquare(i % 8, 2 + i / 8, 0);
		};
	};

	Board(std::array<Piece*, 64> squares, std::array<int, 2> whiteKingPos, std::array<int, 2> blackKingPos) {
		m_squares.swap(squares);
		m_whiteKingPos = whiteKingPos;
		m_blackKingPos = blackKingPos;
	}
	//need destructor defined to clear out objects on heap
	~Board() {
		for (int i = 0; i < 63; i++) {
			delete m_squares[i];
		};
	};

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(m_sprite, states);
	};
	//see above

	bool checkCheck(Piece * piece) {
		return piece->legalMove(*this, !(piece->getColor() + 1) ? m_whiteKingPos : m_blackKingPos);
	};

	void movePiece(std::array<int, 2> currentPos, std::array<int, 2> newPos) {
		Piece * ppiece = inSpace(currentPos);
		if (ppiece->legalMove(*this, newPos)) {

			m_movelist.push_back({ currentPos, newPos });
			ppiece->move(newPos);
			delete m_squares[newPos[0] + 8 * newPos[1]];
			m_squares[newPos[0] + 8 * newPos[1]] = m_squares[currentPos[0] + 8 * currentPos[1]];
			m_squares[currentPos[0] + 8 * currentPos[1]] = new EmptySquare(currentPos[0], currentPos[1], 0);
			std::cout << "Piece Moved!" << std::endl;

			if (currentPos == m_whiteKingPos) {
				m_whiteKingPos = newPos;
			}
			else if (currentPos == m_blackKingPos) {
				m_blackKingPos = newPos;
			}
		}
		else {
			std::cout << "Invalid Move!" << std::endl;
		};
	};
	
	Piece* inSpace(std::array<int, 2> position) {
		return m_squares[position[0] + 8 * position[1]];
	};
};

/*
Board update loop?
Things to implement
- turns
- drawing the objects (should Board handle that and draw all of the pieces too?)
-- will looping through all squares be too slow?
- checkmate checker
- stalemate checker

*/

//Pieces

//Pieces

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
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(m_sprite, states);
	};
	//see above
};

class Knight : public Piece, public sf::Drawable {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	using Piece::Piece;

	bool legalMove(Board board, std::array<int, 2> move) {
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
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(m_sprite, states);
	};
	//see above
};

class Bishop : public Piece, public sf::Drawable {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	using Piece::Piece;

	bool legalMove(Board board, std::array<int, 2> move) {
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
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(m_sprite, states);
	};
	//see above
};

class Rook : public Piece, public sf::Drawable {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	using Piece::Piece;

	bool legalMove(Board board, std::array<int, 2> move) {
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
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(m_sprite, states);
	};
	//see above
};

class Queen : public Piece, public sf::Drawable {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	using Piece::Piece;

	bool legalMove(Board board, std::array<int, 2> move) {
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
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(m_sprite, states);
	};
	//see above
};

class King : public Piece, public sf::Drawable {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	using Piece::Piece;

	bool legalMove(Board board, std::array<int, 2> move) {
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
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(m_sprite, states);
	};
	//see above
};

class EmptySquare : public Piece, public sf::Drawable {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	using Piece::Piece;

	bool legalMove(Board board, std::array<int, 2> move) {
		return false;
	};

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {
		target.draw(m_sprite, states);
	};
	//see above
};