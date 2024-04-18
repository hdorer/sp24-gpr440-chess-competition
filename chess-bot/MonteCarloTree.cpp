#include "MonteCarloTree.h"


namespace ChessSimulator {
	void MonteCarloTree::doMonteCarloTreeSearch() {
		TreeNode current = root;

		
	}

	float MonteCarloTree::visitNode(TreeNode& node) {
		float result;
		
		node.expand();
		node.calculateChildrenUCT();

		TreeNode bestChild = node.bestChild();
		if (bestChild.hasChildren()) {
			result = visitNode(bestChild);
		} else {
			result = bestChild.playout(20);
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