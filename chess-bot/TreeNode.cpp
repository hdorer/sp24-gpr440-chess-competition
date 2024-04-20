#include "TreeNode.h"

#include "BrainRot.h"
#include <sstream>
#include "Utils.h"


namespace ChessSimulator {
	TreeNode::TreeNode(std::string boardFen) {
		chess::Board board(boardFen);

		this->boardFen = boardFen;
		side = board.sideToMove();
		parent = nullptr;
		visits = 0;
		wins = 0.0f;
		uct = FLT_MAX;
	}

	void TreeNode::expand() {
		if (!children.empty()) {
			return;
		}

		chess::Board board(boardFen);
		chess::Movelist legalMoves;
		chess::movegen::legalmoves(legalMoves, board);

		for (chess::Move move : legalMoves) {
			board.makeMove(move);
			children.push_back(TreeNode(board, this));
			board.unmakeMove(move);
		}
	}

	void TreeNode::calculateChildrenUCT() {
		if (children.empty()) {
			return;
		}

		for (int i = 0; i < children.size(); i++) {
			children[i].calculateUCT();
		}
	}

	float TreeNode::playout(BrainRot* bot, int maxMoves) {
		float result;

		chess::Board board(boardFen);

		for (int i = 0; i < maxMoves * 2; i++) {
			if (board.isGameOver().second == chess::GameResult::LOSE) {
				board.makeNullMove();
				if (board.sideToMove() == side) {
					result = 1.0f;
				} else {
					result = -1.0f;
				}
			} else if (board.isGameOver().second == chess::GameResult::DRAW) {
				result = 0.5f;
			} else if (board.isGameOver().second == chess::GameResult::NONE) {
				board.makeMove(getRandomMove(board));
			}
		}

		float sideScore, oppositeSideScore;
		bot->evaluatePosition(board, side, sideScore, oppositeSideScore);
		if (sideScore > oppositeSideScore) {
			result = 1.0f;
		} else if (sideScore < oppositeSideScore) {
			result = -1.0f;
		} else {
			result = 0.5f;
		}

		propagateResult(result);
		return result;
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

	void TreeNode::propagateResult(float result) {
		if (result > 0.0f) {
			wins += result;
		}
		visits++;
	}

	std::string TreeNode::toString() {
		std::stringstream result;

		result << "FEN: " << boardFen << "\nWins: " << wins << "\nVisits: " << visits << "\nWin Rate: " << ((wins / (float)visits) * 100.0f);

		return result.str();
	}

	void TreeNode::calculateUCT() {
		if (visits != 0) {
			uct = (wins / (float)visits) + sqrt(2) * sqrt(log((float)parent->visits) / (float)visits);
		} else {
			uct = FLT_MAX;
		}
	}
}