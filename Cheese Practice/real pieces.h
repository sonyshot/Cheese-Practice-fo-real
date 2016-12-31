#pragma once
#include "Piece.h"

class Pawn : public Piece{
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	Pawn(int size, int file, int rank, int color, sf::Texture * texture, Board * board);

	bool legalMove(std::array<int, 2> move, Board * bufferBoard);

	bool canPromote(std::array<int, 2> move);

	bool canEnPassant(std::array<int, 2> move);

	std::vector<std::array<int, 2>> listLegalMoves(Board * bufferBoard);

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//see above
};

class Knight : public Piece{
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	Knight::Knight(int size, int file, int rank, int color, sf::Texture * texture, Board * board);

	bool legalMove(std::array<int, 2> move, Board * bufferBoard);

	std::vector<std::array<int, 2>> listLegalMoves(Board * bufferBoard);

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//see above
};

class Bishop : public Piece {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	Bishop::Bishop(int size, int file, int rank, int color, sf::Texture * texture, Board * board);

	bool legalMove(std::array<int, 2> move, Board * bufferBoard);

	std::vector<std::array<int, 2>> listLegalMoves(Board * bufferBoard);

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//see above
};

class Rook : public Piece{
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	Rook::Rook(int size, int file, int rank, int color, sf::Texture * texture, Board * board);

	bool legalMove(std::array<int, 2> move, Board * bufferBoard);

	std::vector<std::array<int, 2>> listLegalMoves(Board * bufferBoard);

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//see above
};

class Queen : public Piece {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
	std::string pieceType = "Q";
public:
	Queen::Queen(int size, int file, int rank, int color, sf::Texture * texture, Board * board);

	bool legalMove(std::array<int, 2> move, Board * bufferBoard);

	std::vector<std::array<int, 2>> listLegalMoves(Board * bufferBoard);

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//see above
};

class King : public Piece {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	King::King(int size, int file, int rank, int color, sf::Texture * texture, Board * board);

	bool legalMove(std::array<int, 2> move, Board * bufferBoard);

	bool canCastle(std::array<int, 2> move);

	std::vector<std::array<int, 2>> listLegalMoves(Board * bufferBoard);

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//see above
};

class EmptySquare : public Piece{
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
public:
	EmptySquare();

	EmptySquare(int size, const sf::Texture * texture);

	EmptySquare(int size, int file, int rank, int color, const sf::Texture * texture, Board * board);

	bool legalMove(std::array<int, 2> move, Board * bufferBoard);

	std::vector<std::array<int, 2>> listLegalMoves(Board * bufferBoard);

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//see above
};