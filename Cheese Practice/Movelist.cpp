#include "Movelist.h"

void Movelist::addToMovelist(std::array<int, 2> currentPos, std::array<int, 2> newPos) {
	m_movelist.push_back({ currentPos, newPos });
	m_captureList.push_back(m_board->inSpace(newPos));
}

void Movelist::undoMove() {

}

void Movelist::previousMove() {

}

void Movelist::draw(sf::RenderTarget& target, sf::RenderStates states) const {

}