#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <array>
#include <string>
#include <math.h>
#include <algorithm>
#include "Piece.h"
#include "Movelist.h"
#include <fstream>

class Board : public sf::Drawable {
	friend class Movelist;

	Board * m_buffer;

	Movelist * m_movelist;

	sf::Texture m_boardTexture;

	sf::Texture pawnTexture;
	sf::Texture knightTexture;
	sf::Texture bishopTexture;
	sf::Texture rookTexture;
	sf::Texture queenTexture;
	sf::Texture kingTexture;

	sf::Texture * m_pawnTexture = &pawnTexture;
	sf::Texture * m_knightTexture = &knightTexture;
	sf::Texture * m_bishopTexture = &bishopTexture;
	sf::Texture * m_rookTexture = &rookTexture;
	sf::Texture * m_queenTexture = &queenTexture;
	sf::Texture * m_kingTexture = &kingTexture;

	sf::Sprite m_sprite;

	std::array<Piece*, 64> m_squares = {};

	std::array<Piece*, 16> m_blackPieces = {};
	std::array<Piece*, 16> m_whitePieces = {};

	std::array<int, 2> m_whiteKingPos;
	std::array<int, 2> m_blackKingPos;

	int turn = 1;
	int m_drawCounter = 0;
public:
	//constructor(s) here?

	Board();
	//this uses 'new' to create piece objects that wont get deleted outside the constructor necessitating 'delete' in the destructor
	Board(int size, Board * bufferBoard);
	//plz use multiple of 8 for board creation

	Board(int size, std::array<Piece*, 64> squares, std::array<int, 2> whiteKingPos, std::array<int, 2> blackKingPos);
	//need destructor defined to clear out objects on heap
	~Board();

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//see above

	std::vector<Piece*> inCheckCheck();

	bool checkmateCheck(std::array<int, 2> testPos, std::vector<Piece*> checkingPieces);

	bool stalemateCheck();

	void movePiece(std::array<int, 2> currentPos, std::array<int, 2> newPos);

	void move(std::array<int, 2> currentPos, std::array<int, 2> newPos);

	void updateMoveList(std::array<int, 2> currentPos, std::array<int, 2> newPos);

	void validMove(std::array<int, 2> currentPos, std::array<int, 2> newPos);
	
	void undoMove();

	std::vector<Piece*> coveredSquare(std::array<int, 2> testPos, int color);

	std::array<int, 2> kingPosition(int color);

	Piece* inSpace(std::array<int, 2> position);

	std::array<std::array<int, 2>, 2> previousMove();

	int whichTurn();

	void writeMovelistToFile(std::string file);
};