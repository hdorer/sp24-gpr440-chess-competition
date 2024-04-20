#include "MonteCarloTree.h"

#include "BrainRot.h"


namespace ChessSimulator {
	void MonteCarloTree::doMonteCarloTreeSearch() {
		TreeNode current = root;

		
	}

	float MonteCarloTree::visitNode(TreeNode& node, BrainRot* bot) {
		float result;
		
		node.expand();
		node.calculateChildrenUCT();

		TreeNode bestChild = node.bestChild();
		if (bestChild.hasChildren()) {
			result = visitNode(bestChild);
		} else {
			result = bestChild.playout(bot, 20);
		}

		if (result == 1.0f) {
			result = -1.0f;
		}
		if (result == -1.0f) {
			result = 1.0f;
		}

		node.propagateResult(result);

		return result;
	}
}