#pragma once
#ifndef BOARD_H
#define BOARD_H

class Movelist;

#include <string>
#include <math.h>
#include <algorithm>
#include <fstream>
#include "Piece.h"
#include "StateManager.h"

class Board : public ApplicationState {
	friend class Movelist;

	int m_xPos, m_yPos, m_size;

	Board * m_buffer;

	Movelist * m_movelist;

	Piece * m_heldPiece = NULL;

	sf::Texture m_boardTexture;
	sf::Texture m_MMbuttonTexture;
	sf::Texture m_RestartButtonTexture;

	sf::Sprite m_RestartButtonSprite;
	sf::Sprite m_MMbuttonSprite;

	sf::Texture pawnTexture;
	sf::Texture knightTexture;
	sf::Texture bishopTexture;
	sf::Texture rookTexture;
	sf::Texture queenTexture;
	sf::Texture kingTexture;

	sf::Sprite m_sprite;

	std::array<Piece*, 64> m_squares = {};

	std::vector<Piece*> m_blackPieces = {};
	std::vector<Piece*> m_whitePieces = {};

	std::array<int, 2> m_whiteKingPos;
	std::array<int, 2> m_blackKingPos;
	
	int m_drawCounter = 0;
	std::vector<int> m_drawCountOnTurn;
public:
	
	int turn = 1;

	Board();
	//this uses 'new' to create piece objects that wont get deleted outside the constructor necessitating 'delete' in the destructor
	Board(int size, StateManager * stateManager);
	//add statemanager pointer to constructor
	//plz use multiple of 8 for board creation

	Board(int size, std::array<Piece*, 64> squares, std::array<int, 2> whiteKingPos, std::array<int, 2> blackKingPos);
	//need destructor defined to clear out objects on heap
	~Board();

	//this needs to be redone/actually done; although this seems to work
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	std::vector<Piece*> inCheckCheck();

	bool checkmateCheck(std::array<int, 2> testPos, std::vector<Piece*> checkingPieces);

	bool stalemateCheck();

	void movePiece(std::array<int, 2> currentPos, std::array<int, 2> newPos);

	void move(std::array<int, 2> currentPos, std::array<int, 2> newPos);

	void validMove(std::array<int, 2> currentPos, std::array<int, 2> newPos);
	
	void undoMove();

	std::vector<Piece*> coveredSquare(std::array<int, 2> testPos, int color);

	std::array<int, 2> kingPosition(int color);

	Piece* inSpace(std::array<int, 2> position);

	std::array<std::array<int, 2>, 2> previousMove();

	void writeMovelistToFile(std::string file);

	bool insufficientMaterial();

	void flipBoard();

	void handleEvent(const sf::Event &eventHandled);
};
#endif