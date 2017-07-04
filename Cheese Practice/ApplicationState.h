#pragma once
#ifndef APPLICATIONSTATE_H
#define APPLICATIONSTATE_H

class StateManager;

#include <SFML\Graphics.hpp>
#include <array>
#include <iostream>

class ApplicationState :public sf::Drawable {
protected:
	StateManager * m_stateManager = NULL;
public:
	virtual void handleEvent(const sf::Event &eventHandled) = 0;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

enum class PossibleStates { MENUSTATE1, BOARDSTATE };

#endif // !APPLICATIONSTATE_H