#include <SFML/Graphics.hpp>
#include "board.h"
#include "real pieces.h"

//copy pasta'd window loop from sfml website
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "board drawing test");
	Board board(400);

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		};

		window.clear();
		window.draw(board);
		window.display();
	};

	return 0;
};