#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <array>
#include <string>
#include "Piece.h"

class Board : public sf::Drawable {
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

	std::array<int, 2> m_whiteKingPos;
	std::array<int, 2> m_blackKingPos;

	std::vector<std::array<std::array<int, 2>, 2>> m_movelist;
	std::vector<std::string> m_captureList;
	std::vector<std::array<int, 2>> m_capturePosList;

	std::string m_printMoves = "Movelist:";
	sf::Font m_font;
	sf::Text m_text;

	int turn = 1;
public:
	//constructor(s) here?
	//this uses 'new' to create piece objects that wont get deleted outside the constructor necessitating 'delete' in the destructor
	Board(int size);
	//plz use multiple of 8 for board creation

	Board(int size, std::array<Piece*, 64> squares, std::array<int, 2> whiteKingPos, std::array<int, 2> blackKingPos);
	//need destructor defined to clear out objects on heap
	~Board();

	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	//see above

	bool inCheckCheck(std::array<int, 2> kingPos);

	void movePiece(std::array<int, 2> currentPos, std::array<int, 2> newPos);
	
	void undoMove();

	Piece * recreatePiece(int file, int rank, int color, std::string identifier);

	Piece* inSpace(std::array<int, 2> position);

	std::array<std::array<int, 2>, 2> previousMove();
};