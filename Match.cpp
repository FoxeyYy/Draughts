#include "Draughts.hpp"
#include <cstdlib>
#include <iostream>

Match::Match(Player& player1, Player& player2): player1(player1), player2(player2) {};

void Match::start() {

	PlayerTurn turn = getRandomTurn();
	Player *currentPlayer;

	while(true) {

		std::cout << board << std::endl;

		if (!board.playerCanMove(PLAYER1) && !board.playerCanMove(PLAYER2)) {
			std::cout << "Draw!" << std::endl;
			break;
		} else if (!board.playerCanMove(PLAYER1)) {
			std::cout << "Player 2 wins!" << std::endl;
			break;
		} else if (!board.playerCanMove(PLAYER2)) {
			std::cout << "Player 1 wins!" << std::endl;
			break;
		}

		switch(turn) {
			case PLAYER1:
				currentPlayer = &player1;
				break;
			case PLAYER2:
				currentPlayer = &player2;
				break;
		}


		Movement nextMove = currentPlayer->getMovement(&board);

		if(!nextMove.isValid(currentPlayer->getTurn())) {
			std::cout << "Not a valid movement, please retry" << std::endl;
			continue;
		}

		nextMove.execute();
		//std::cin.get();
		std::cout << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl << std::endl;

		if (turn == PLAYER1) turn = PLAYER2;
		else turn = PLAYER1;
		
	}

}

PlayerTurn Match::getRandomTurn() {

	srand (time(NULL));
	int randomInt = rand() % 2 + 1;

	switch (randomInt) {
		case 1: return PLAYER1;
		case 2: return PLAYER2;
		default: std::cerr << "Random player error";
			exit(EXIT_FAILURE);
	}

}