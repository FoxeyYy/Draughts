#include "Draughts.hpp"
#include <random>

RandomAIPlayer::RandomAIPlayer(PlayerTurn turn): Player(turn) {

}

Movement RandomAIPlayer::getMovement(Board* board) {

	auto origins = board->piecesWithFreedomOf(turn);

 	std::random_device rd;
    	std::mt19937 gen(rd());
	std::uniform_int_distribution<int> dis(0, origins.size() - 1);
	Position origin {origins.at(dis(gen))};

	auto destinies = board->possibleDestiniesFor(origin);
	std::uniform_int_distribution<int> dis2(0, destinies.size() - 1);
	Position destiny {destinies.at(dis2(gen))};

	return Movement{origin, destiny, board, true};
}