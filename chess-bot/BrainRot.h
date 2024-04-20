#pragma once

#include <string>
#include <chess.hpp>
#include <map>

namespace ChessSimulator {
	class BrainRot {
	public:
		BrainRot();

		chess::Color getSide() const;
		void setSide(bool side);

		bool isWhite() const;
		chess::Move getNextMove(chess::Board& board);

		void evaluatePosition(chess::Board& board, float& whiteScore, float& blackScore);
		void evaluatePosition(chess::Board& board, chess::Color side, float& sideScore, float& oppositeSideScore);
		float evaluatePosition(chess::Board& board);

	private:
		chess::Color side;

		std::map<chess::PieceType, int> pieceValues;
		std::map<chess::PieceType, std::map<chess::Color, int*>> pieceSquareTables;
		float materialWeight = 0.3f;
		float positionalWeight = 0.3f;
		float attackWeight = 0.2f;
		float checkWeight = 0.2f;

		float evaluateForSide(chess::Board& board, chess::Color side);
	};
}