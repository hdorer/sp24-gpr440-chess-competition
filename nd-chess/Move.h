#pragma once

#include <stdint.h>
#include "Types.h"
#include <vector>


namespace NDChess {
	struct Move {
	public:
		int startIndex;
		int endIndex;
		PieceTypeBit pieceType;
		ColorBit pieceColor;
		std::string moveString;

		Move(PieceTypeBit pieceType, ColorBit pieceColor, int startIndex, int endIndex, const Board* board) : startIndex(startIndex), endIndex(endIndex), pieceType(pieceType), pieceColor(pieceColor), moveString(toString(board)) { }

	private:
		std::string toString(const Board* board) const;
	};

	class Board;
	
	class MoveRules {
	public:
		static std::vector<Move> pawn(const Board* board, int index, bool attacksOnly = false);
		static std::vector<Move> knight(const Board* board, int index);
		static std::vector<Move> bishop(const Board* board, int index);
		static std::vector<Move> rook(const Board* board, int index);
		static std::vector<Move> queen(const Board* board, int index);
		static std::vector<Move> king(const Board* board, int index);

	private:
		static std::vector<Move> bishop(const Board* board, int index, int distanceCap);
		static std::vector<Move> rook(const Board* board, int index, int distanceCap);
		static std::vector<Move> queen(const Board* board, int index, int distanceCap);

		static bool pawnMove(std::vector<Move>& moveList, const Board* board, int startIndex, int endIndex);
		static bool pawnAttack(std::vector<Move>& moveList, const Board* board, int startIndex, int endIndex);
		static void lineMove(std::vector<Move>& moveList, const Board* board, int startIndex, int increment, int distanceCap);
	};


}