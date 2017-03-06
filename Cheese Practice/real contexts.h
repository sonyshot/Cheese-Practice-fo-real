#pragma once

#ifndef REALCONTEXTS_H
#define REALCONTEXTS_H

#include "AppContext.h"

class Game :public AppContext {
	Board * m_board = NULL;
	//game pieces texture goes here
	//create new board constructor that takes a texture and uses it when creating the pieces
public:
	Game();

	Game(int boardSize);

	~Game();

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

class LoadingScreen :public AppContext {

};

class Menu :public AppContext {

};

#endif // !REALCONTEXTS_H