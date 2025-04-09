#pragma once
#ifndef GAME_HPP_
#define GAME_HPP_

#include <iostream>
#include "board.hpp"

struct Move {
	int color, startRow, startCol, endRow, endCol;
	bool jump;
};

class Game {
public:
	Board* board;
private:
	bool currentPlayer = 0;
	bool gameOver = 0;
	std::vector<Move> moves;

public:
	Game(bool backJump = false, bool mandJump = false, int noStartRows = 3, bool turn = true);
	Game(const Game& g);
	~Game();
	void start();
	void restart();
	std::pair<Board*, bool> playTurn(int startRow, int startCol, int endRow, int endCol);
	void switchTurn();
	bool getTurn() const;
	bool isGameOver();
	Board* getCurrentState() const;
	void setCurrentState(Board* b);
	void saveGame(std::string path) const;
	void loadGame(std::string path);

	bool aiTurn();
	Board* aiMove(Board* b);
};

#endif // !GAME_HPP_