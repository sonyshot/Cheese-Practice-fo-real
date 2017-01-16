#include "Piece.h"
#include "Board.h"

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
Piece::Piece(int size, int file, int rank, int color, sf::Texture * texture, Board * board, std::string identifier) {
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
	m_sprite.setPosition(sf::Vector2f((float)(file * size), (float)(7-rank) * size));
	m_currentBoard = board;
	m_name = identifier;
};

void Piece::move(std::array<int, 2> newPos) {
	m_position.swap(newPos);
	m_sprite.setPosition(sf::Vector2f(m_position[0]*m_size, (7-m_position[1])*m_size));
};
void Piece::dragPiece(std::array<int, 2> movement) {
	m_sprite.setPosition(sf::Vector2f((float)movement[0], (float)movement[1]));
};
bool Piece::canCastle(std::array<int, 2> move) {
	return false;
};

bool Piece::canPromote(std::array<int, 2> move) {
	return false;
};

bool Piece::canEnPassant(std::array<int, 2> move) {
	return false;
};

int Piece::hasMoved() {
	return m_numMoves;
};

void Piece::decrementMoves() {
	m_numMoves--;
};

void Piece::incrementMoves() {
	m_numMoves++;
}

int Piece::getColor() {
	return m_color;
};
std::string Piece::getName() {
	return m_name;
}
std::array<int, 2> Piece::getPosition() {
	return m_position;
};

void Piece::setCapture(bool capture) {
	m_isCaptured = capture;
};

bool Piece::isCaptured() {
	return m_isCaptured;
};

bool Piece::operator==(const Piece& piece) const {
	if (m_position == piece.m_position && m_color == piece.m_color && m_name == piece.m_name && m_isCaptured == piece.m_isCaptured)
		return true;
	else
		return false;
}