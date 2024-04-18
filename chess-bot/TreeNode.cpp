#include "TreeNode.h"

#include "Utils.h"


namespace ChessSimulator {
	void TreeNode::expand() {
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

	void TreeNode::calculateChildrenUCT() {
		if (children.empty()) {
			return;
		}

		for (TreeNode node : children) {
			node.calculateUCT();
		}
	}

	float TreeNode::playout(int maxMoves) {
		chess::Board board(boardFen);

		for (int i = 0; i < maxMoves * 2; i++) {
			board.makeMove(getRandomMove(board));
			// if(board.isGameOver().second == chess::GameResult::)
		}

		return 0.0f;
	}

	TreeNode& TreeNode::bestChild() {
		int bestIndex = 0;
		float bestUCT = -FLT_MAX;

		for (int i = 0; i < children.size(); i++) {
			if (children[i].uct > bestUCT) {
				bestIndex = i;
				bestUCT = children[i].uct;
			}
		}

		return children[bestIndex];
	}

	void TreeNode::calculateUCT() {
		if (visits != 0) {
			uct = (wins / (float)visits) + sqrt(2) * sqrt(log((float)parent->visits) / (float)visits);
		} else {
			uct = FLT_MAX;
		}
	}
}