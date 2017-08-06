#include "Draughts.hpp"
#include <iostream>

HumanPlayer::HumanPlayer(PlayerTurn turn): Player(turn) {

}

Movement HumanPlayer::getMovement(Board* board) {

	std::cout << *this << ", your turn:" ;

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