#include "TreeNode.h"

#include "BrainRot.h"
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

	float TreeNode::playout(BrainRot* bot, int maxMoves) {
		chess::Board board(boardFen);
		chess::Color side = board.sideToMove();

		for (int i = 0; i < maxMoves * 2; i++) {
			board.makeMove(getRandomMove(board));
			if (board.isGameOver().second == chess::GameResult::LOSE) {
				board.makeNullMove();
				if (board.sideToMove() == side) {
					return 1.0f;
				} else {
					return -1.0f;
				}
			} else if (board.isGameOver().second == chess::GameResult::DRAW) {
				return 0.5f;
			}
		}

		float sideScore, oppositeSideScore;
		bot->evaluatePosition(board, side, sideScore, oppositeSideScore);
		if (sideScore > oppositeSideScore) {
			return 1.0f;
		} else if (sideScore < oppositeSideScore) {
			return -1.0f;
		} else {
			return 0.5f;
		}
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