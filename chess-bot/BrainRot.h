#pragma once

#include <string>
#include <chess.hpp>
#include <map>

namespace ChessSimulator {
	namespace PieceSquareTables {
		// Table value source: https://www.chessprogramming.org/PeSTO%27s_Evaluation_Function
		extern int blackPawn[64];
		extern int blackKnight[64];
		extern int blackBishop[64];
		extern int blackRook[64];
		extern int blackQueen[64];
		extern int blackKing[64];

		extern int whitePawn[64];
		extern int whiteKnight[64];
		extern int whiteBishop[64];
		extern int whiteRook[64];
		extern int whiteQueen[64];
		extern int whiteKing[64];
	}

	class BrainRot {
	public:
		BrainRot();

		chess::Color getSide() const;
		void setSide(bool side);

		bool isWhite() const;
		chess::Move getNextMove(chess::Board& board);

		void evaluatePosition(chess::Board& board, int& whiteScore, int& blackScore);

	private:
		std::map<chess::PieceType, int> pieceValues;
		std::map<chess::PieceType, std::map<chess::Color, int*>> pieceSquareTables;
		chess::Color side;

		int evaluateForSide(chess::Board& board, chess::Color side);
		chess::Move getRandomMove(chess::Board& board);
	};
}