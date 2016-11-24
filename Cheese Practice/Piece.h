#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <array>

class Board;

class Piece: public sf::Drawable {
protected:
	std::array<int, 2> m_position;
	int m_color;
	sf::Sprite m_sprite;
public:
	Piece();

	Piece(int file, int rank, int color);

	std::array<int, 2> getPosition();

	void move(std::array<int, 2> newPos);

	int getColor();

	virtual bool legalMove(Board board, std::array<int, 2> move);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates state);
};

