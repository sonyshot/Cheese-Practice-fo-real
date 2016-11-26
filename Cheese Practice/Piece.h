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
	float m_size;
	Board * m_currentBoard;
	std::string m_name;
public:
	Piece();

	Piece(int size, const sf::Texture texture);

	Piece(int size, int file, int rank, int color, sf::Texture * texture, Board * board, std::string identifier);

	std::array<int, 2> getPosition();

	virtual void move(std::array<int, 2> newPos);

	int getColor();

	std::string getName();

	virtual bool legalMove(std::array<int, 2> move) = 0;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

