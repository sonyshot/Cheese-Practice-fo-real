#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <array>

class Board: public sf::Drawable{
	sf::Sprite m_sprite;
	Piece *m_squares[64];
	std::array<int, 2> m_whiteKingPos;
	std::array<int, 2> m_blackKingPos;
public:
	//constructor(s) here?
	Board() {
		
	};
	//end constructor
	//this needs to be redone/actually done
	void draw(sf::RenderTarget& target, sf::RenderStates states) const {

	};
	//see above

	bool checkCheck(Piece * piece) {
		
	};



	Piece* inSpace(std::array<int, 2> position) {
		
	};
};
class Piece {
protected:
	std::array<int, 2> m_position;
	int m_color;
	sf::Sprite m_sprite;
public:

	std::array<int, 2> getPosition();

	void move(std::array<int, 2> newPos);

	int getColor();

	virtual bool legalMove(Board board, std::array<int, 2> move);
};
class Pawn : public Piece, public sf::Drawable {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
};
class Knight : public Piece, public sf::Drawable {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
};
class Bishop : public Piece, public sf::Drawable {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
};
class Rook : public Piece, public sf::Drawable {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
};
class Queen : public Piece, public sf::Drawable {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
};
class King : public Piece, public sf::Drawable {
	//inherits m_position, m_sprite, m_color
	//inherits getPosition, getColor, move
};