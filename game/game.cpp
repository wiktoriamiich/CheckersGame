#include "game.hpp"
#include "algorithm.hpp"

Game::Game(bool backJump, bool mandJump, int noStartRows, bool turn) {
	board = new Board(backJump, mandJump, noStartRows);
	currentPlayer = turn;
	start();
}

Game::Game(const Game& g) {
	this->board = new Board(*g.board);
	this->currentPlayer = g.currentPlayer;
	this->gameOver = g.gameOver;
	this->moves = g.moves;
}

Game::~Game() {
	delete board;
}

void Game::start() {
	gameOver = 0;
	currentPlayer = WHITE - 1;
}

void Game::restart() {
	board->reset();
	start();
}

std::pair<Board*, bool> Game::playTurn(int startRow, int startCol, int endRow, int endCol) {
	if (gameOver) return std::make_pair(nullptr, false);
	bool jump = false;
	if (board->isJump(startRow, startCol, endRow, endCol)) {
		jump = true;
	}
	if (board->movePiece(startRow, startCol, endRow, endCol)) {
		switchTurn();
	}
	else return std::make_pair(nullptr, false);
	return std::make_pair(board, jump);
}

void Game::switchTurn() {
	currentPlayer = !currentPlayer;
}

bool Game::getTurn() const {
	return currentPlayer;
}

// TO-DO
bool Game::isGameOver() {
	if (board->whitePieces == 0 || board->blackPieces == 0) {
		gameOver = 1;
	}
	return gameOver;
}

Board* Game::getCurrentState() const {
	return board;
}

void Game::setCurrentState(Board* b) {
	board = b;
}

void Game::saveGame(std::string path) const {
	return;
}

void Game::loadGame(std::string path) {
	return;
}

bool Game::aiTurn() {
	Board* aiBoard = this->aiMove(this->getCurrentState());
	if (aiBoard != nullptr) {
		this->setCurrentState(aiBoard);
		return true;
	}
	return false;
}

Board* Game::aiMove(Board* b) {
	this->board = b;
	std::pair<std::pair<int, Board>, std::pair<std::pair<int, int>, bool>> bestMove = minimax(std::pair<int, int>(-1, -1), 3, true, *this);
	this->board = new Board(bestMove.first.second);
	// TO-DO: Implement multiple jumps for AI
	if (bestMove.second.second) {
		auto jumps = this->board->getValidJumps(bestMove.second.first.first, bestMove.second.first.second);
		if (jumps.size() > 0) {
			std::pair<std::pair<int, Board>, std::pair<std::pair<int, int>, bool>> bestMove = minimax(std::pair<int, int>(bestMove.second.first.first, bestMove.second.first.second), 2, true, *this);
			this->board = new Board(bestMove.first.second);
		}
	}
	switchTurn();
	return board;
}