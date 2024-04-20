#pragma once

#include <chess.hpp>
#include <string>


namespace ChessSimulator {
	class TreeNode {
	public:
		TreeNode(std::string fen, TreeNode* parent) : boardFen(fen), parent(parent) { }

		std::vector<TreeNode>& getChildren() { return children; }

		void expand();
		void calculateChildrenUCT();
		float playout(class BrainRot* bot, int maxMoves);

		bool hasChildren() const { return !children.empty(); }
		TreeNode& bestChild();
		void propagateResult(float result) { wins += result; }
	private:
		std::string boardFen;
		chess::Color side;
		int visits;
		float wins;
		float uct;

		TreeNode* parent;
		std::vector<TreeNode> children;

		void calculateUCT();
	};
}