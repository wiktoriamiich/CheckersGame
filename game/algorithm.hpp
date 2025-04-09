#pragma once
#ifndef MINIMAX_ALGORITHM_HPP_
#define MINIMAX_ALGORITHM_HPP_

#include "game.hpp"

std::pair<std::pair<int, Board>, std::pair<std::pair<int, int>, bool>> minimax(std::pair<int, int> pos, int depth, bool max_player, Game game);

#endif // !MINIMAX_ALGORITHM_HPP_