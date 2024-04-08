#pragma once

#include <stdint.h>
#include "Types.h"
#include <vector>


namespace NDChess {
	struct Move {
		int startIndex;
		int endIndex;

		Move(int startIndex, int endIndex) {
			this->startIndex = startIndex;
			this->endIndex = endIndex;
		}
	};

	class Board;
	
	class MoveRules {
	public:
		static std::vector<Move> pawn(Board* board, int index, ColorBit color, bool attacksOnly = false);
		static std::vector<Move> knight(Board* board, int index, ColorBit color);
		static std::vector<Move> bishop(Board* board, int index, ColorBit color);
		static std::vector<Move> rook(Board* board, int index, ColorBit color);
		static std::vector<Move> queen(Board* board, int index, ColorBit color);
		static std::vector<Move> king(Board* board, int index, ColorBit color);

	private:
		static std::vector<Move> bishop(Board* board, int index, ColorBit color, int distanceCap);
		static std::vector<Move> rook(Board* board, int index, ColorBit color, int distanceCap);
		static std::vector<Move> queen(Board* board, int index, ColorBit color, int distanceCap);

		static bool pawnMove(std::vector<Move>& moveList, Board* board, int startIndex, int endIndex);
		static bool pawnAttack(std::vector<Move>& moveList, Board* board, int startIndex, int endIndex, ColorBit color);
		static void lineMove(std::vector<Move>& moveList, Board* board, int startIndex, int increment, ColorBit color, int distanceCap);
	};
}