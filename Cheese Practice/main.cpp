#define _CRT_SECURE_NO_WARNINGS
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "real pieces.h"
#include "StateManager.h"
#include <fstream>
#include <stdio.h>
#include <time.h>

//copy pasta'd window loop from sfml website

int main()
{
	float fps = 60.f;
	sf::Time sleepTime(sf::seconds(1.f/fps));
	sf::Clock clock;

	sf::RenderWindow window(sf::VideoMode(1000, 1000), "board drawing test");

	StateManager gameState(&window);


	while (window.isOpen())
	{
	//testing menu screen, etc.
		//game loop
		clock.restart();

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			gameState.processEvent(event);
		}
		//maybe eventually wrap all the window loop into a gameState update function?
		//might make animations more doable
		window.clear();
		gameState.draw();
		window.display();
		if (clock.getElapsedTime() < sleepTime)
			sf::sleep(sleepTime - clock.getElapsedTime());

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
- add 'flipped board' functionality, probably best to convert input and output than to make adjustments in base code to account for it *UNDONE* (undoing a band-aid solution,
	eventually would like pieces to not store their own position and have the board handle where to draw them)
- have the legal moves of selected piece be highlighted
- generalize piece/board sizes to allow for scaling of the board
- add sleep/timer for a 60 fps update loop *DONE* (i think)
- logging to txt file(s)
- 

---might be possible to remove emptySquares and replace them with NULL on the board
---Using vector.reserve()
---setting dangling pointers to NULL after deleting their objects
*/