#include "Draughts.hpp"
#include <iostream>

void showOptions() {
	std::cout <<	"0 Human player" << std::endl
		  <<	"1 Random AI" << std::endl
		  <<	"2 Alpha Beta Pruning AI" << std::endl << std::endl;
}

Player::Type getPlayerType() {
	int type;
	std::cin >> type;
	return (Player::Type)type;
}

main() {
	
	showOptions();
	std::cout << "Type black pieces player type: ";
	Player &player1 = Player::create(PLAYER1, getPlayerType());

	std::cout << "Type white pieces player type: ";
	Player &player2 = Player::create(PLAYER2, getPlayerType());
	
	Match match {player1, player2};
	match.start();
}