#include "Draughts.hpp"
#include <iostream>

PlayerTurn Board::getOwner(Position pos) {
	return board[pos.getRow()][pos.getCol()].owner;

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
				if (!newDestiny.withinBounds()) break;
				if (MAN == getAt(origin).type && length > 1) break;
				if (getAt(newDestiny).owner == getAt(origin).owner) break;

				Movement eatMov {origin, newDestiny, this};
				if ( 	getAt(newDestiny).type == EMPTY ||
					(getAt(newDestiny).owner != getAt(origin).owner) &&
					eatMov.canEat()) {
						destinies.push_back(newDestiny);
				}

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