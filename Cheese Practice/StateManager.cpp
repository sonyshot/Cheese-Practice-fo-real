#include "StateManager.h"
#include "MainMenu.h"
#include "Board.h"

StateManager::StateManager(sf::RenderWindow *window) {

	m_window = window;
	m_states[0] = new MainMenu(this);
	m_states[1] = new Board(800, this);

}

StateManager::~StateManager() {

	delete m_states[0];
	delete m_states[1];

}

void StateManager::switchState(PossibleStates newState) {
	m_currentState = newState;
}

//i might like to make an event queue to prevent breaking when objects call for changes on themselves, like deleting or something
//these could go into a container and be cleared out each "update" loop (which would also need to be added)
void StateManager::processEvent(const sf::Event &e) {
	if (m_currentState == PossibleStates::MENUSTATE1) {
		m_states[0]->handleEvent(e);
	}
	else if (m_currentState == PossibleStates::BOARDSTATE) {
		m_states[1]->handleEvent(e);
	}
}

void StateManager::restartChess() {
	delete m_states[1];
	m_states[1] = new Board(800, this);
}

void StateManager::closeWindow() {
	m_window->close();
}

void StateManager::draw() {
	if (m_currentState == PossibleStates::MENUSTATE1) {
		m_window->draw(*m_states[0]);
	}
	else if (m_currentState == PossibleStates::BOARDSTATE) {
		m_window->draw(*m_states[1]);
	}
}