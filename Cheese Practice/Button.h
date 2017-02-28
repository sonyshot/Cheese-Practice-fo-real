#pragma once

#ifndef BUTTON_H
#define BUTTON_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <functional>


class Button :public sf::Drawable {
	//currently this will assume a rectangular shaped button
	sf::Texture * m_texture;
	sf::Sprite m_sprite;
	std::function<void()> m_action;
public:
	Button(sf::Vector2f, sf::Texture*, std::function<void()>);

	void execute();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const = 0;
};
#endif // !BUTTON_H
