#include "Piece.h"

Piece::Piece() {
	m_position = { 0, 0 };
	m_color = 1;
	m_size = 100.f;
};
Piece::Piece(int size, const sf::Texture texture) {
	m_position = { 0, 0 };
	m_color = 1;
	m_sprite.setTexture(texture);
	if (size != 100) {//current piece textures are 100x100, this scales appropriately if the board is a different size
		m_size = (float)size;
		m_sprite.scale(m_size / 100.f, m_size / 100.f);
	};
	m_size = 100.f;
};
Piece::Piece(int size, int file, int rank, int color, sf::Texture * texture) {
	m_position = { file, rank };

	//-1 for black, 1 for white, 0 for empty square
	m_color = color;

	m_sprite.setTexture(*texture);
	if (size != 100) {//current piece textures are 100x100, this scales appropriately if the board is a different size
		m_size = (float)size;
		m_sprite.scale(m_size / 100.f, m_size / 100.f);
	};
	m_size = 100.f;
	if (color == -1) {
		m_sprite.setColor(sf::Color::Black);
	}
	m_sprite.setPosition(sf::Vector2f(file * size, (7-rank) * size));
};

std::array<int, 2> Piece::getPosition() {
	return m_position;
};

void Piece::move(std::array<int, 2> newPos) {
	m_position.swap(newPos);
	m_sprite.setPosition(sf::Vector2f(m_position[0]*m_size, (7-m_position[1])*m_size));
};
int Piece::getColor() {
	return m_color;
};