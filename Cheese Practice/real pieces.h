#pragma once
#include "Piece.h"

class Pawn : public Piece{
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	using Piece::Piece;

	bool legalMove(Board board, std::array<int, 2> move);

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//see above
};

class Knight : public Piece{
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	using Piece::Piece;

	bool legalMove(Board board, std::array<int, 2> move);

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//see above
};

class Bishop : public Piece {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	using Piece::Piece;

	bool legalMove(Board board, std::array<int, 2> move);

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//see above
};

class Rook : public Piece{
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	using Piece::Piece;

	bool legalMove(Board board, std::array<int, 2> move);

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//see above
};

class Queen : public Piece {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	using Piece::Piece;

	bool legalMove(Board board, std::array<int, 2> move);

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//see above
};

class King : public Piece {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	using Piece::Piece;

	bool legalMove(Board board, std::array<int, 2> move);

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//see above
};

class EmptySquare : public Piece{
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	EmptySquare();

	EmptySquare(int size, const sf::Texture texture);

	EmptySquare(int size, int file, int rank, int color, const sf::Texture texture);

	bool legalMove(Board board, std::array<int, 2> move);

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//see above
};