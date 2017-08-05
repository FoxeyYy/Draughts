#include "Draughts.hpp"

main() {
	Player player1{PLAYER1};
	Player player2{PLAYER2};
	Match match {player1, player2};
	match.start();
}