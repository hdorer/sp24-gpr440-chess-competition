#include "TreeNode.h"


namespace ChessSimulator {
	void TreeNode::generateChildren() {
		if (!children.empty()) {
			return;
		}

		chess::Board board(boardFen);
		chess::Movelist legalMoves;
		chess::movegen::legalmoves(legalMoves, board);

		for (chess::Move move : legalMoves) {
			board.makeMove(move);
			children.push_back(TreeNode(board.getFen(), this));
			board.unmakeMove(move);
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