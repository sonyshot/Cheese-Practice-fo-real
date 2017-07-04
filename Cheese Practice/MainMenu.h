#pragma once
#ifndef MAINMENU_H
#define MAINMENU_H

#include "StateManager.h"

class MainMenu :public ApplicationState {
	int m_currentSelection = 0;

	sf::Font m_font;
	sf::Text m_headerText, m_menuChoice1Text, m_menuChoice2Text, m_menuChoice3Text;

	std::array<sf::Text *, 3> m_menuChoices = {&m_menuChoice1Text, &m_menuChoice2Text, &m_menuChoice3Text};
public:
	MainMenu(StateManager* stateManager);

	void handleEvent(const sf::Event &eventHandled);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

#endif