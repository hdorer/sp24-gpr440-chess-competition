#include "TreeNode.h"


namespace ChessSimulator {
	void TreeNode::generateChildren(chess::Board& board) {
		if (!children.empty()) {
			return;
		}

		chess::Movelist legalMoves;
		chess::movegen::legalmoves(legalMoves, board);

		for (chess::Move move : legalMoves) {
			children.push_back(TreeNode(move, this));
		}
	}

	void TreeNode::calculateUCT() {
		if (visits != 0) {
			uct = (wins / visits) + sqrt(2) * sqrt(log(parent->visits) / visits);
		} else {
			uct = FLT_MAX;
		}
	}
}