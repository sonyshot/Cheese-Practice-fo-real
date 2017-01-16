#include "Button.h"

Button::Button(sf::Vector2f position, sf::Texture* texture, std::function<void()> action):m_action(action), m_texture(texture) {
	m_sprite.setTexture(*texture);
	m_sprite.setPosition(position);
	//assumes texture size matches the desired button size
}

void Button::execute() {
	m_action();
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	target.draw(m_sprite);
}