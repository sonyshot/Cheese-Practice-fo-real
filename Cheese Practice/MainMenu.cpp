#include "MainMenu.h"

MainMenu::MainMenu(StateManager * stateManager) {
	if (!m_font.loadFromFile("C:\\Windows\\Fonts\\arial.ttf"))
		std::cout << "failed to load font" << std::endl;
	//set font, string, fillcolor, position
	m_headerText.setFont(m_font);
	m_headerText.setFillColor(sf::Color::White);
	m_headerText.setPosition(sf::Vector2f(460.f, 100.f));
	for (int i = 0; i < 3; i++) {
		m_menuChoices[i]->setFont(m_font);
		m_menuChoices[i]->setFillColor(sf::Color::White);
		m_menuChoices[i]->setPosition(sf::Vector2f(200.f, 200.f + 100.f*i));
	};
	m_headerText.setString("Chessy Chess");
	m_menuChoices[0]->setString("Chess");
	m_menuChoices[1]->setString("Inactive");
	m_menuChoices[2]->setString("Quit");

	m_menuChoice1Text.setFillColor(sf::Color::Red);
	m_stateManager = stateManager;
}

void MainMenu::handleEvent(const sf::Event &e) {
	switch (e.type) {

	case sf::Event::KeyPressed:
		if (e.key.code == sf::Keyboard::Down) {
			m_menuChoices[m_currentSelection]->setFillColor(sf::Color::White);
			m_currentSelection = (m_currentSelection + 1) % 3;
			m_menuChoices[m_currentSelection]->setFillColor(sf::Color::Red);

		} else if (e.key.code == sf::Keyboard::Up) {
			m_menuChoices[m_currentSelection]->setFillColor(sf::Color::White);
			m_currentSelection = (m_currentSelection + 2) % 3;
			m_menuChoices[m_currentSelection]->setFillColor(sf::Color::Red);

		}
		else if (e.key.code == sf::Keyboard::Return) {
			if (m_currentSelection == 0) {
				m_stateManager->switchState(PossibleStates::BOARDSTATE);
			}
			else if (m_currentSelection == 2) {
				m_stateManager->closeWindow();
			}
		}
		break;
	}
}

void MainMenu::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_headerText);
	target.draw(m_menuChoice1Text);
	target.draw(m_menuChoice2Text);
	target.draw(m_menuChoice3Text);
}