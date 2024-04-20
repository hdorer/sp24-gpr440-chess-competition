#pragma once

#include <chess.hpp>
#include <string>


namespace ChessSimulator {
	class TreeNode {
	public:
		TreeNode(chess::Board& board, TreeNode* parent) : boardFen(board.getFen()), side(board.sideToMove()), parent(parent), visits(0), wins(0.0f), uct(FLT_MAX) { }
		TreeNode(std::string boardFen);

		std::vector<TreeNode>& getChildren() { return children; }

		void expand();
		void calculateChildrenUCT();
		float playout(class BrainRot* bot, int maxMoves);

		bool hasChildren() const { return !children.empty(); }
		bool hasBeenVisited() const { return visits > 0; }
		TreeNode& bestChild();
		void propagateResult(float result);

		std::string toString();
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