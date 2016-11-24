#include <SFML/Graphics.hpp>
#include "board and pieces.cpp"

//copy pasta'd window loop from sfml website
int main()
{
	sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		};

		window.clear();
		window.draw(shape);
		window.display();
	};

	return 0;
};