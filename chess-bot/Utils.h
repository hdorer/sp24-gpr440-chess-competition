#pragma once

#include <chess.hpp>


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

	const int BEST_POSSIBLE_MATERIAL = 39;
	const int BEST_POSSIBLE_POSITIONAL_SCORE = 1334;

	chess::Color oppositeColor(chess::Color);
}