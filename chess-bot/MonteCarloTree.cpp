#include "MonteCarloTree.h"

#include "BrainRot.h"
#include <cmath>


namespace ChessSimulator {
	chess::Move MonteCarloTree::getBestMove(BrainRot* bot) {
		for (int i = 0; i < 1000; i++) {
			visitNode(&root, bot);
		}

		TreeNode* bestMove = root.bestChild();
		
		chess::Board board(root.getBoardFen());
		chess::Movelist legalMoves;
		chess::movegen::legalmoves(legalMoves, board);

		for(int i = 0; i < legalMoves.size(); i++) {
			board.makeMove(legalMoves[i]);
			if(board.getFen() == bestMove->getBoardFen()) {
				return legalMoves[i];
			}
			board.unmakeMove(legalMoves[i]);
		}

		return legalMoves[0];
	}

	float MonteCarloTree::visitNode(TreeNode* node, BrainRot* bot) {
		float result = 0.0f;
		
		if(!node->expand()) {
			result = node->boardResult();
		} else {
			node->calculateChildrenUCT();

			TreeNode* next;

			if (!node->allChildrenVisited()) {
				next = node->firstUnvisitedChild();
			} else {
				next = node->mostPromisingChild();
			}
			
			if (next->hasBeenVisited()) {
				result = visitNode(next, bot);
			} else {
				result = next->playout(bot, 20);
			}

			if (result == 1.0f) {
				result = -1.0f;
			}
			else if (result == -1.0f) {
				result = 1.0f;
			}
		}

		node->propagateResult(result);

		return result;
	}
}