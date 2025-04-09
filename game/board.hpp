#ifndef BOARD_HPP_
#define BOARD_HPP_

#include <vector>
#include "piece.hpp"

const int BOARD_SIZE = 8;

class Board {
	Piece* board[BOARD_SIZE][BOARD_SIZE];
	bool backwardJump = false,
		mandatoryJump = false;
	int noStartRows = 3;

public:
	int whitePieces = 12;
	int blackPieces = 12;
	int whiteKings = 0;
	int blackKings = 0;

	Board(bool backJump = false, bool mandJump = false, int noStartRows = 3);
	Board(const Board& b);

	void display() const;
	void reset();
	//void changeBoardSize(int newSize);
	//void setBackwardJump(bool backJump);

	bool movePiece(int startRow, int startCol, int endRow, int endCol);
	bool jumpPiece(int startRow, int startCol, int endRow, int endCol);
	bool isOccupied(int row, int col) const;
	bool isJump(int startRow, int startCol, int endRow, int endCol) const;

	Piece* getPiece(int row, int col) const;
	std::vector<std::pair<int, int>> getValidMoves(int row, int col) const;
	std::vector<std::pair<int, int>> getValidJumps(int row, int col) const;
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> allAvailableMoves(int player) const;
	std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> allAvailableJumps(int player) const;

	int evaluate() const;

private:
	bool isValidMove(int startRow, int startCol, int endRow, int endCol) const; 
	bool move(int startRow, int startCol, int endRow, int endCol);
};


#endif // !BOARD_HPP_
