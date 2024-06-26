#pragma once

#include <chess.hpp>
#include "TreeNode.h"
#include <string>


namespace ChessSimulator {
	class MonteCarloTree {
	public:
		MonteCarloTree(std::string boardFen) : root(boardFen) { }

		chess::Move getBestMove(class BrainRot* bot);

	private:
		TreeNode root;

		float visitNode(TreeNode* node, class BrainRot* bot);
	};
}