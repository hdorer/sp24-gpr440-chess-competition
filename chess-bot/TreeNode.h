#pragma once

#include <chess.hpp>
#include <string>


namespace ChessSimulator {
	class TreeNode {
	public:
		TreeNode(chess::Board& board, TreeNode* parent) : boardFen(board.getFen()), side(board.sideToMove()), parent(parent), visits(0), wins(0.0f), uct(FLT_MAX) { }
		TreeNode(std::string boardFen);

		std::vector<TreeNode>& getChildren() { return children; }

		bool expand();
		void calculateChildrenUCT();
		TreeNode& bestChild();

		bool hasBeenVisited() const { return visits > 0; }
		float playout(class BrainRot* bot, int maxMoves);
		float boardResult();
		void propagateResult(float result);

		bool hasChildren() const { return !children.empty(); }

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
		float boardResult(chess::Board& board);
	};
}