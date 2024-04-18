#pragma once

#include <chess.hpp>
#include "TreeNode.h"
#include <string>


namespace ChessSimulator {
	class MonteCarloTree {
	public:
		MonteCarloTree(std::string boardFen) : root(boardFen, nullptr) { }

		void doMonteCarloTreeSearch();
	private:
		TreeNode root;

		float visitNode(TreeNode& node);
	};
}