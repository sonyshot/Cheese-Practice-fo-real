#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <array>
#include "Piece.h"

class Board : public sf::Drawable {
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	std::array<Piece*, 64> m_squares = {};
	std::array<int, 2> m_whiteKingPos;
	std::array<int, 2> m_blackKingPos;
	std::vector<std::array<std::array<int, 2>, 2>> m_movelist;
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

	bool checkCheck(Piece * piece);

	void movePiece(std::array<int, 2> currentPos, std::array<int, 2> newPos);

	Piece* inSpace(std::array<int, 2> position);
};