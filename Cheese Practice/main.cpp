#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include "board.h"
#include "Piece.h"
#include "real pieces.h"
#include <fstream>
#include <stdio.h>
#include <time.h>

//copy pasta'd window loop from sfml website

int main()
{
	int windowState = 1;
	sf::RenderWindow window(sf::VideoMode(1000, 800), "board drawing test");
	int boardCreated = 0;

	Board bBuffer;
	Board * buffer = &bBuffer;
	Board board(800, buffer);
	std::array<int, 2> clicky;
	int selectionFlag = 0;
	Piece* pieceHeld = NULL;
	bool flippedBoard = 0;

	sf::RectangleShape rectangle;
	rectangle.setSize(sf::Vector2f(800, 800));
	rectangle.setFillColor(sf::Color::Red);


	while (window.isOpen())
	{
		//testing menu screen, etc.
		while (windowState == 0) {
			//game loop
			sf::Event event;
			while (window.pollEvent(event))
			{
				switch (event.type)
				{
					// window closed
				case sf::Event::Closed:
				{
					window.close();
					/*time_t rawtime;
					time(&rawtime);
					std::ofstream myfile("ErrorLog.txt", std::ofstream::app);
					myfile << asctime(localtime(&rawtime));
					myfile.close();
					board.writeMovelistToFile("ErrorLog.txt");*/
					windowState = -1;
					break;
				}
					// key pressed
				case sf::Event::MouseButtonPressed:
					if (event.mouseButton.x < 800 && event.mouseButton.y < 800) {
						selectionFlag = 1;
						if (!flippedBoard)
							clicky = { event.mouseButton.x / 100, 7 - event.mouseButton.y / 100 };
						else
							clicky = { event.mouseButton.x / 100, event.mouseButton.y / 100 };
						pieceHeld = board.inSpace(clicky);
					}
					else if(event.mouseButton.y > 400 && event.mouseButton.y < 800){
						windowState = 1;
					}
					else if (event.mouseButton.y < 400){
						board.inSpace(board.previousMove()[1])->decrementMoves();
						board.undoMove();
						std::cout << "move undone" << std::endl;
					}
					else
						flippedBoard = !flippedBoard;
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
						if (!flippedBoard) {
							std::array<int, 2> released = { event.mouseButton.x / 100, 7 - event.mouseButton.y / 100 };
							if (pieceHeld->legalMove(released, buffer)) {
								board.movePiece(clicky, released);
								bBuffer.movePiece(clicky, released);
								pieceHeld->incrementMoves();
								std::cout << "valid move" << std::endl;
							}
							else {
								std::cout << "invalid move" << std::endl;
								pieceHeld->dragPiece({ clicky[0] * 100, (7 - clicky[1]) * 100 });
							}
							selectionFlag = 0;
						}
						else {
							std::array<int, 2> released = { event.mouseButton.x / 100, event.mouseButton.y / 100 };
							if (pieceHeld->legalMove(released, buffer)) {
								board.movePiece(clicky, released);
								bBuffer.movePiece(clicky, released);
								pieceHeld->incrementMoves();
								std::cout << "valid move" << std::endl;
							}
							else {
								std::cout << "invalid move" << std::endl;
								pieceHeld->dragPiece({ clicky[0] * 100, (clicky[1]) * 100 });
							}
							selectionFlag = 0;
						}
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
		}
		while (windowState == 1) {
			//starting menu loop
			sf::Event event;
			while (window.pollEvent(event)) {
				switch (event.type) {

				case sf::Event::Closed:
					window.close();
					windowState = -1;
					break;

				case sf::Event::MouseButtonPressed:
					windowState = 0;
					break;
				}
			}
			window.clear();
			window.draw(rectangle);
			window.display();
		}
	};


	return 0;
};

/*
Board update loop?
Things to implement
- turns *DONE*
- drawing the objects (should Board handle that and draw all of the pieces too?) *DONE*
- checkmate checker *DONE*
- stalemate checker *DONE* (currently working on 50 moves sans capture *DONE* and insufficient checkmating material *DONE*)
- seeing movelist *DONE*
- undo button *DONE* (functions exactly right, UI for it isnt implemented)
-- will need special considerations for special moves
- *this* inside class functions is apparently unneccessary, clean it up! *DONE*
- add 'flipped board' functionality, probably best to convert input and output than to make adjustments in base code to account for it
- have the legal moves of selected piece be highlighted
- generalize piece/board sizes to allow for scaling of the board
- add sleep/timer for a 60 fps update loop
- logging to txt file(s)

---Using vector.reserve()
---setting dangling pointers to NULL after deleting their objects
*/