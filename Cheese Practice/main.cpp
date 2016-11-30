#include <SFML/Graphics.hpp>
#include "board.h"
#include "Piece.h"
#include "real pieces.h"

//copy pasta'd window loop from sfml website
int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 800), "board drawing test");
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
				if (event.mouseButton.x > 800 && event.mouseButton.y < 100) {
					board.undoMove();
					std::cout << "move undone" << std::endl;
				}
				else if (selectionFlag == 0) {
					clicky = { event.mouseButton.x / 100, 7 - event.mouseButton.y / 100 };
					selectionFlag = 1;
					std::cout << "Piece selected position x: " << clicky[0] << " y: " << clicky[1] << std::endl;
				}
				else {
					board.movePiece(clicky, { event.mouseButton.x / 100, 7 - event.mouseButton.y / 100 });
					selectionFlag = 0;
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

/*
Board update loop?
Things to implement
- turns *DONE*
- drawing the objects (should Board handle that and draw all of the pieces too?) *DONE*
-- will looping through all squares be too slow?
- checkmate checker
- stalemate checker
- seeing movelist /in progress/
- undo button /in progress/ (functions exactly right, UI for it isnt implemented)
-- will need special considerations for special moves
- go through and remove this->inspace in this file (maybe not, we'll see)
- *this* inside class functions is apparently unneccessary, clean it up!

*/