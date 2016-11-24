#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <array>

class Board;

class Piece {
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

	virtual bool legalMove(Board board, std::array<int, 2> move) = 0;
};

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
			if ((move[0] == m_position[0]) && !(board->inSpace(move)->getColor())) {
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