#pragma once

#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <iostream>
#include <SFML\Graphics.hpp>
#include "real pieces.h"
#include "Board.h"
#include "Button.h"

class AppContext :public sf::Drawable {
	
public:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};

#endif // !APPCONTEXT_H