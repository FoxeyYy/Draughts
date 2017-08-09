#include "Draughts.hpp"
#include <iostream>

Player::Player(PlayerTurn turn): turn(turn) {
	
}

Player& Player::create(PlayerTurn turn, Type type) {
	switch (type) {
		case HUMAN:
			return *new HumanPlayer(turn);
		case RANDOM_AI:
			return *new RandomAIPlayer(turn);
		case AB_AI:
			return *new AlphaBetaAIPlayer(turn);
	}

}

PlayerTurn Player::getTurn() {
	return turn;
}

Position::Col Player::getColFromChar(char col) {
	switch (col) {
		case 'A': return Position::Col::A;
		case 'B': return Position::Col::B;
		case 'C': return Position::Col::C;
		case 'D': return Position::Col::D;
		case 'E': return Position::Col::E;
		case 'F': return Position::Col::F;
		case 'G': return Position::Col::G;
		case 'H': return Position::Col::H;
		default: return Position::Col::NOT_VALID;
	}
}

std::ostream& operator <<(std::ostream& outputStream, const Player& p) {
	if (PLAYER1 == p.turn) {
		outputStream << "Player 1 (Black)";
	} else {
		outputStream << "Player 2 (White)";
	}

	return outputStream;
}