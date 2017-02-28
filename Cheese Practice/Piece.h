#pragma once
#ifndef PIECE_H
#define PIECE_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <array>

class Board;

class Piece: public sf::Drawable {
protected:
	std::array<int, 2> m_position;
	int m_color;
	int m_numMoves = 0;
	sf::Sprite m_sprite;
	float m_size;
	Board * m_currentBoard;
	std::string m_name;
	bool m_isCaptured = 0;
	bool m_isFlipped = 0;
public:
	Piece();

	Piece(int size, const sf::Texture texture);

	Piece(int size, int file, int rank, int color, sf::Texture * texture, Board * board, std::string identifier);

	std::array<int, 2> getPosition();

	virtual void move(std::array<int, 2> newPos);

	void dragPiece(std::array<int, 2> movement);

	virtual bool canCastle(std::array<int, 2> move);

	virtual bool canPromote(std::array<int, 2> move);

	virtual bool canEnPassant(std::array<int, 2> move);

	virtual std::vector<std::array<int, 2>> listLegalMoves(Board * bufferBoard) = 0;

	int getColor();

	void setCapture(bool capture);

	bool isCaptured();

	std::string getName();

	int hasMoved();

	void incrementMoves();

	void decrementMoves();

	void flipBoard();

	virtual bool legalMove(std::array<int, 2> move, Board * bufferBoard) = 0;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;

	bool operator==(const Piece& piece) const;
};

enum class ChessMoves {NORMAL, CASTLE, PROMOTION, ENPASSANT};

#endif // !PIECE_H