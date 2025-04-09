#include "algorithm.hpp"
#include <climits>
#include <iostream>


// Funkcja minimax zwraca par� par:
// - pierwsza para to wynik ewaluacji, najlepsza plansza i informacja o ruchu skoku
// - druga para to najlepszy ruch do wykonania i czy by� to ruch skoku
std::pair<std::pair<int, Board>, std::pair<std::pair<int, int>, bool>> minimax(std::pair<int, int> pos, int depth, bool max_player, Game game) {
    Board board = Board(*game.getCurrentState());


    // Warunek ko�cz�cy rekurencj� - osi�gni�to maksymaln� g��boko�� lub koniec gry
    if (depth == 0 || game.isGameOver()) {
        return std::make_pair(std::make_pair((*game.getCurrentState()).evaluate(), board), std::make_pair(std::make_pair(-1, -1), false));
    }
    
    // Inicjalizacja zmiennych do oceny ruch�w
    int maxEval = INT_MIN, minEval = INT_MAX;
    Board bestBoard;
    std::pair<int, int> bestMove = std::make_pair(-1, -1);
    bool bestJump = false;

    if (max_player) {

        // Iterujemy po wszystkich mo�liwych ruchach dla pierwszego gracza
        for (auto& move : board.allAvailableMoves(1)) {
            Game newGame = game; // Make a new copy of the game state
            std::pair<Board*, bool> result = newGame.playTurn(move.first.first, move.first.second, move.second.first, move.second.second);
            
            // Sprawdzamy poprawno�� wykonanego ruchu
            if (result.first == nullptr) {
                std::cerr << "Invalid move! [minimax()!!!]" << std::endl;
                continue;
            }

            // Rekurencyjnie wywo�ujemy minimax dla kolejnego poziomu drzewa gry
            int eval = minimax(std::make_pair(move.second.first, move.second.second), depth - 1, false, newGame).first.first;
            
            // Wybieramy najlepszy wynik dla maksymalizuj�cego gracza
            if (eval > maxEval) {
                maxEval = eval;
                bestBoard = Board(*newGame.getCurrentState());
                bestMove = move.second;
                bestJump = result.second;
            }
        }

        // Zwracamy najlepszy wynik dla maksymalizuj�cego gracza
        return std::make_pair(std::make_pair(maxEval, bestBoard), std::make_pair(bestMove, bestJump));
    }
    else {
        for (auto& move : board.allAvailableMoves(2)) {
            // Tworzymy now� kopi� stanu gry
            Game newGame = game; // Make a new copy of the game state
            std::pair<Board*, bool> result = newGame.playTurn(move.first.first, move.first.second, move.second.first, move.second.second);
            
            // Sprawdzamy poprawno�� wykonanego ruchu
            if (result.first == nullptr) {
                std::cerr << "Invalid move! [minimax()!!!]" << std::endl;
                continue;
            }

            // Rekurencyjnie wywo�ujemy minimax dla kolejnego poziomu drzewa gry
            int eval = minimax(std::make_pair(move.second.first, move.second.second), depth - 1, true, newGame).first.first;
            
            // Wybieramy najlepszy wynik dla minimalizuj�cego gracza
            if (eval < minEval) {
                minEval = eval;
                bestBoard = Board(*newGame.getCurrentState());
                bestMove = move.second;
                bestJump = result.second;
            }
        }

        // Zwracamy najlepszy wynik dla minimalizuj�cego gracza
        return std::make_pair(std::make_pair(minEval, bestBoard), std::make_pair(bestMove, bestJump));
    }
}