#include "Draughts.hpp"
#include <limits>

#define PLY 6
int orow, drow;
Position::Col ocol, dcol;

AlphaBetaAIPlayer::AlphaBetaAIPlayer(PlayerTurn turn): Player(turn) {

}

Movement AlphaBetaAIPlayer::getMovement(Board *board) {
	search(*board, PLY, std::numeric_limits<int>::min(), std::numeric_limits<int>::max(), true);
	return Movement{Position{orow, ocol}, Position{drow, dcol}, board, true};
}

int AlphaBetaAIPlayer::search(Board &board, int depth, int a, int b, bool maximizing) {

	int bestValue;

	if (	depth == 0 ||
		!board.playerCanMove(PLAYER1) ||
		!board.playerCanMove(PLAYER2)) {
			return heuristic(board);
	} 

	if (maximizing) {
		bestValue = a;
		auto origins = board.piecesWithFreedomOf(turn);
		for (auto origin: origins) {
			auto destinies = board.possibleDestiniesFor(origin);
			for (auto destiny: destinies) {
				Movement move {origin, destiny, &board, true};
				move.execute();
				int childValue = search(board, depth - 1, bestValue, b, false);
				move.undo();
				if (childValue > bestValue) {
					if (depth == PLY) {
						orow = origin.getRow();
						ocol = origin.getCol();
						drow = destiny.getRow();
						dcol = destiny.getCol();
					}
					bestValue = childValue;
				}

				if (b <= bestValue) return bestValue;
			}
		}
		
		return bestValue;

	} else  {
		bestValue = b;
		auto origins = board.piecesWithFreedomOf((PlayerTurn)(1 - turn));
		for (auto origin: origins) {
			auto destinies = board.possibleDestiniesFor(origin);
			for (auto destiny: destinies) {
				Movement move {origin, destiny, &board, true};
				move.execute();
				bestValue = std::min(bestValue, search(board, depth - 1, a, bestValue, true));
				move.undo();
				if (bestValue <= a) return bestValue;
			}
		}
		
		return bestValue;
	}

}

int AlphaBetaAIPlayer::heuristic(Board &board) {
	PlayerTurn othersTurn = (PlayerTurn)(1 - turn);

	if (!board.playerCanMove(turn)) return std::numeric_limits<int>::min();
	if (!board.playerCanMove(othersTurn)) return std::numeric_limits<int>::max();

	int piecesFactor = 	3*(board.getPiecesFor(turn, KING) - board.getPiecesFor(othersTurn, KING)) +
				1*(board.getPiecesFor(turn, MAN) - board.getPiecesFor(othersTurn, MAN));
	int kingsProximityFactor = board.scoreByDistanceToKings(turn) - board.scoreByDistanceToKings(othersTurn);
	int invPiecesFactor = 2*(board.numInvenciblePiecesFor(turn, KING) - board.numInvenciblePiecesFor(othersTurn, KING)) +
				(board.numInvenciblePiecesFor(turn, MAN) - board.numInvenciblePiecesFor(othersTurn, MAN));
	int unusablePiecesFactor = 2*(board.numUnusablePiecesFor(turn, KING) - board.numUnusablePiecesFor(othersTurn, KING)) + 
					(board.numUnusablePiecesFor(turn, MAN) - board.numUnusablePiecesFor(othersTurn, MAN));
	int randomComponent = (rand() % 10);

	return 1000*piecesFactor + 100*kingsProximityFactor + 10*(1.2*invPiecesFactor - unusablePiecesFactor) + randomComponent;
}

