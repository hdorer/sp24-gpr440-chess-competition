#pragma once

#include <chess.hpp>


namespace ChessSimulator {
	class TreeNode {
	public:
		TreeNode(chess::Move move, TreeNode* parent) : move(move), parent(parent) { }

		void generateChildren(chess::Board& board);
		void calculateUCT();
	private:
		chess::Move move;
		chess::Color side;
		int visits;
		int wins;
		float uct;

		TreeNode* parent;
		std::vector<TreeNode> children;
	};
}