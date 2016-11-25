#include "Piece.h"

Piece::Piece() {
	m_position = { 0, 0 };
	m_color = 1;
};
Piece::Piece(int size, const sf::Texture texture) {
	m_position = { 0, 0 };
	m_color = 1;
	m_sprite.setTexture(texture);
	if (size != 100) {//current piece textures are 100x100, this scales appropriately if the board is a different size
		m_sprite.scale((float)size / 100.f, (float)size / 100.f);
	};
};
Piece::Piece(int size, int file, int rank, int color, const sf::Texture texture) {
	m_position = { file, rank };

	//-1 for black, 1 for white, 0 for empty square
	m_color = color;

	m_sprite.setTexture(texture);
	if (size != 100) {//current piece textures are 100x100, this scales appropriately if the board is a different size
		m_sprite.scale((float)size / 100.f, (float)size / 100.f);
	};
	if (color == -1) {
		m_sprite.setColor(sf::Color::Black);
	}
	m_sprite.setPosition(sf::Vector2f(file * size, rank * size));
};

std::array<int, 2> Piece::getPosition() {
	return m_position;
};

void Piece::move(std::array<int, 2> newPos) {
	m_position.swap(newPos);
};
int Piece::getColor() {
	return m_color;
};