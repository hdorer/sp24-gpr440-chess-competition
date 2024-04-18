#pragma once

#include <chess.hpp>
#include <string>


namespace ChessSimulator {
	class TreeNode {
	public:
		TreeNode(std::string fen, TreeNode* parent) : boardFen(fen), parent(parent) { }

		void generateChildren();
		void calculateUCT();
	private:
		std::string boardFen;
		chess::Color side;
		int visits;
		int wins;
		float uct;

		TreeNode* parent;
		std::vector<TreeNode> children;
	};
}