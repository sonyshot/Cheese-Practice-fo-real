
#include <SFML/Graphics.hpp>
#include "board.h"
#include "Piece.h"
#include "real pieces.h"

//copy pasta'd window loop from sfml website

int main()
{
	sf::RenderWindow window(sf::VideoMode(1000, 800), "board drawing test");
	Board bBuffer;
	Board * buffer = &bBuffer;
	Board board(800, buffer);
	std::array<int, 2> clicky;
	int selectionFlag = 0;
	Piece* pieceHeld = NULL;

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
				if (event.mouseButton.x < 800) {
					selectionFlag = 1;
					clicky = { event.mouseButton.x / 100, 7 - event.mouseButton.y / 100 };
					pieceHeld = board.inSpace(clicky);
				}
				else {
					board.undoMove();
					std::cout << "move undone" << std::endl;
				}
				break;
				/*
				*****This is the original click once to pick a piece and click again to move it to a square*****

				if (event.mouseButton.x > 800 && event.mouseButton.y < 100) {
					board.undoMove();
					std::cout << "move undone" << std::endl;
				}
				else if (selectionFlag == 0) {
					clicky = { event.mouseButton.x / 100, 7 - event.mouseButton.y / 100 };
					selectionFlag = 1;
					std::cout << "Piece selected position x: " << clicky[0] << " y: " << clicky[1] << std::endl;
					std::cout << "Standard board moves " << board.inSpace(clicky)->hasMoved() << std::endl;
					std::cout << "Buffer board moves " << buffer->inSpace(clicky)->hasMoved() << std::endl;
				}
				else {
					std::cout << "Trying to move to x:" << event.mouseButton.x / 100 << " y:" << 7 - event.mouseButton.y / 100 << std::endl;
					board.validMove(clicky, { event.mouseButton.x / 100, 7 - event.mouseButton.y / 100 });
					selectionFlag = 0;
				}
				break;
				*/
			case sf::Event::MouseMoved:
				if (selectionFlag) {
					pieceHeld->dragPiece({ event.mouseMove.x - 50, event.mouseMove.y - 50 });
				}
				break;
			case sf::Event::MouseButtonReleased:
				if (selectionFlag) {
					if (pieceHeld->legalMove({ event.mouseButton.x / 100, 7 - event.mouseButton.y / 100 }, buffer)) {
						board.movePiece(clicky, { event.mouseButton.x / 100, 7 - event.mouseButton.y / 100 });
						bBuffer.movePiece(clicky, { event.mouseButton.x / 100, 7 - event.mouseButton.y / 100 });
						std::cout << "valid move" << std::endl;
					}
					else {
						std::cout << "invalid move" << std::endl;
						pieceHeld->dragPiece({ clicky[0] * 100, (7 - clicky[1]) * 100 });
					}
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
- checkmate checker *DONE*
- stalemate checker
- seeing movelist *DONE*
- undo button *DONE* (functions exactly right, UI for it isnt implemented *DONE*)
-- will need special considerations for special moves
- *this* inside class functions is apparently unneccessary, clean it up! *DONE*
- add 'flipped board' functionality, probably best to convert input and output than to make adjustments in base code to account for it

*/