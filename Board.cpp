#include "Draughts.hpp"
#include <iostream>

PlayerTurn Board::getOwner(Position pos) {
	return board[pos.getRow()][pos.getCol()].owner;

}

int Board::getPiecesFor(PlayerTurn player, PieceType type) {
	int numPieces = 0;

	for(int i=0; i<NUM_ROWS; i++) {
		for(int j=0; j<NUM_COLS; j++) {
			if (	player == board[i][j].owner && 
				type == board[i][j].type) {
				numPieces++;
			}
		}
	}

	return numPieces;
}

int Board::scoreByDistanceToKings(PlayerTurn player) {
	int score = 0;
	int firstRow = player == PLAYER1 ? 0: NUM_ROWS;
	int lastRow = NUM_ROWS - firstRow;
	int direction = player == PLAYER1 ? 1: -1;

	for (int row = firstRow; row<lastRow; row+=direction) {
		for (int col = 0; col<NUM_COLS; col++) {
			if (board[row][col].owner == player &&
				board[row][col].type == MAN) {
				score += row+1;
			}
		}
	}

	return score;

}

int Board::numInvenciblePiecesFor(PlayerTurn player, PieceType type) {
	int numPieces = 0;

	for(int i=0; i<NUM_ROWS; i++) {
		for(int j=0; j<NUM_COLS; j++) {
			if (	player == board[i][j].owner && 
				type == board[i][j].type && 
				!pieceCanBeEaten(Position{i, (Position::Col)j})) {
				numPieces++;
			}
		}
	}

	return numPieces;
}

int Board::numUnusablePiecesFor(PlayerTurn player, PieceType type) {
	int numPieces = 0;

	for(int i=0; i<NUM_ROWS; i++) {
		for(int j=0; j<NUM_COLS; j++) {
			if (	player == board[i][j].owner && 
				type == board[i][j].type && 
				!pieceHasFreedom(Position{i, (Position::Col)j})) {
				numPieces++;
			}
		}
	}

	return numPieces;
}

bool Board::playerCanMove(PlayerTurn player) {
	for(int i=0; i<NUM_ROWS; i++) {
		for(int j=0; j<NUM_COLS; j++) {
			if (	player == board[i][j].owner && 
				pieceHasFreedom(Position{i, (Position::Col)j})) {
				return true;
			}
		}
	}

	return false;
}

bool Board::pieceHasFreedom(Position position) {
	int movements[2] {-1, 1};

	for (int rowMov: movements) {
		for (int colMov: movements) {
			int 	newRow = position.getRow() + rowMov,
				newCol = position.getCol() + colMov;
			Position adyPosition {newRow, (Position::Col) newCol};

			if (!adyPosition.withinBounds()) continue;

			if (	EMPTY == board[newRow][newCol].type ||
				Movement{position, adyPosition, this}.canEat()) {
				return true;
			}
		}
	}
	
	return false;
}

bool Board::pieceCanBeEaten(Position pos) {
	int movements[2] {-1, 1};

	for (int rowMov: movements) {
		for (int colMov: movements) {
			Position origin {pos.getRow() + rowMov, (Position::Col)(pos.getCol() + colMov)};
			if (!origin.withinBounds() || 
				board[origin.getRow()][origin.getCol()].owner ==
				board[pos.getRow()][pos.getCol()].owner) continue;

			Movement mov{origin, pos, this};
			Position next = mov.getNextPosition();
			if (!next.withinBounds()) continue;
			if (board[next.getRow()][next.getCol()].owner != board[pos.getRow()][pos.getCol()].owner) {
				return true;
			}			
		}
	}
	
	return false;
}

std::vector<Position> Board::piecesWithFreedomOf(PlayerTurn player) {
	std::vector<Position> positions{};

	for(int i=0; i<NUM_ROWS; i++) {
		for(int j=0; j<NUM_COLS; j++) {
			Position position {Position{i, (Position::Col)j}};
			if (	player == board[i][j].owner && 
				pieceHasFreedom(position)) {
				positions.push_back(position);
			}
		}
	}

	return positions;
}

std::vector<Position> Board::possibleDestiniesFor(Position origin) {
	std::vector<Position> destinies;
	short offsets[] = {-1, 1};

	for(short rowOffset: offsets) {
		for (short colOffset: offsets) {
			int length = 1;
			while (true) {
				Position newDestiny {origin.getRow() + length*rowOffset, (Position::Col) (origin.getCol() + length*colOffset)};
				Movement eatMov {origin, newDestiny, this};
				if ( !eatMov.isValid(getAt(origin).owner)) break;
				destinies.push_back(newDestiny);
				length++;
			}

			
		}
	}

	return destinies;
}

Piece Board::getAt(Position pos) {
	return board[pos.getRow()][pos.getCol()];
}

Piece& Board::operator ()(int row, int col) {
	return board[row][col];
}

std::ostream& operator <<(std::ostream& outputStream, const Board& board) {

	outputStream << "A \tB \tC \tD \tE \tF \tG \tH" << std::endl;

	for(int i=0; i<NUM_ROWS; i++) {
		for (int j=0; j<NUM_COLS; j++) {
			switch(board.board[i][j].type) {
				case MAN:
					if (board.board[i][j].owner == PLAYER1) outputStream << 'b' << "\t";
					else outputStream << 'w' << "\t";
					break;
				case KING:
					if (board.board[i][j].owner == PLAYER1) outputStream << 'B' << "\t";
					else outputStream << 'W' << "\t";
					break;
				default:
					outputStream << '-' << "\t";
					break;
			}
		}
		outputStream << i+1 << std::endl;
	}

	return outputStream;
}