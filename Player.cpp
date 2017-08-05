#include "Draughts.hpp"
#include <iostream>

Player::Player(PlayerTurn turn): turn(turn) {
	
}

Movement Player::getMovement(Board* board) {

	int orRow, desRow;
	char orCol, desCol;

	std::cin >> orCol >> orRow >> desCol >> desRow;

	orRow--;
	desRow--;

	Position::Col orRealCol = getColFromChar(orCol);
	Position::Col desRealCol = getColFromChar(desCol);
	
	Position origin{orRow, orRealCol};
	Position destiny{desRow, desRealCol};
	return Movement{origin, destiny, board, true};
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