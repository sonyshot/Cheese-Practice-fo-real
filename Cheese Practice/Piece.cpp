#include "Piece.h"

Piece::Piece() {
	m_position = { 0, 0 };
	m_color = 1;
};
Piece::Piece(int file, int rank, int color) {
	m_position = { file, rank };

	//-1 for black, 1 for white, 0 for empty square
	m_color = color;
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