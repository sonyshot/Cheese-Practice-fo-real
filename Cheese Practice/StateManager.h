#pragma once
#ifndef STATEMANAGER_H
#define STATEMANAGER_H

#include "ApplicationState.h"

class StateManager {
	//i guess i need to remove the buffer board mess because its creating more complexity
	PossibleStates m_currentState = PossibleStates::MENUSTATE1;

	std::array<ApplicationState*, 2> m_states;

	sf::RenderWindow * m_window;

public:
	StateManager(sf::RenderWindow *window);

	StateManager(std::array<ApplicationState*, 2>);

	~StateManager();

	void switchState(PossibleStates);

	void closeWindow();

	void restartChess();

	void processEvent(const sf::Event &e);

	void draw();
};

#endif // !STATEMANAGER_H