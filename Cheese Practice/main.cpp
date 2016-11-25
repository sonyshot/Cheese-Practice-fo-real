#include <SFML/Graphics.hpp>
#include "board.h"
#include "Piece.h"
#include "real pieces.h"

//copy pasta'd window loop from sfml website
int main()
{
	sf::RenderWindow window(sf::VideoMode(800, 800), "board drawing test");
	Board board(800);
	std::array<int, 2> clicky;
	int selectionFlag = 0;

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				// window closed
			case sf::Event::Closed:
				window.close();
				break;

				// key pressed
			case sf::Event::MouseButtonPressed:
				if (selectionFlag == 0) {
					clicky = { event.mouseButton.x / 100, event.mouseButton.y / 100 };
					selectionFlag = 1;
					std::cout << "Piece selected position x: " << clicky[0] << " y: " << clicky[1] << std::endl;
				}
				else {
					board.movePiece(clicky, { event.mouseButton.x / 100, event.mouseButton.y / 100 });
					selectionFlag = 0;
					std::cout << "is something happening?" << std::endl;
				}
				break;

				// we don't process other types of events
			default:
				break;
			}
		};

		window.clear();
		window.draw(board);
		window.display();
	};

	return 0;
};