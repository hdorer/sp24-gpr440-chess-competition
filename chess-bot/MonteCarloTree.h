#pragma once

#include <chess.hpp>
#include "TreeNode.h"
#include <string>


namespace ChessSimulator {
	class MonteCarloTree {
	public:
		MonteCarloTree(std::string boardFen) : root(boardFen, nullptr) { }

		chess::Move getBestMove();
	private:
		TreeNode root;
	};
}