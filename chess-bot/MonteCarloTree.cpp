#include "MonteCarloTree.h"

#include "BrainRot.h"


namespace ChessSimulator {
	std::string MonteCarloTree::getBestMove(BrainRot* bot) {
		for (int i = 0; i < 100; i++) {
			visitNode(root, bot);
		}

		return root.bestChild().toString();
	}

	float MonteCarloTree::visitNode(TreeNode& node, BrainRot* bot) {
		float result;
		
		if(!node.expand()) {
			result = node.boardResult();
		}
		node.calculateChildrenUCT();

		TreeNode& bestChild = node.bestChild();
		if (bestChild.hasBeenVisited()) {
			result = visitNode(bestChild, bot);
		} else {
			result = bestChild.playout(bot, 20);
		}

		if (result == 1.0f) {
			result = -1.0f;
		} else if (result == -1.0f) {
			result = 1.0f;
		}

		node.propagateResult(result);

		return result;
	}
}