#pragma once

#include <iostream>
#include "Types.h"


namespace NDChess {
	class Board {
	public:
		Board();

		void clear();
		void clear(int index);
		void setPositionFromFen(std::string fen);
		void printRawView();

		bool isPieceHere(int index) const { return (bool)(squares[index] & PIECE_HERE_MASK); }
		ColorBit getColor(int index) const;
		PieceTypeBit getPieceType(int index) const;
	private:
		static const int NUM_SQUARES = 64;
		uint8_t squares[NUM_SQUARES];

		ColorBit sideToMove;

		const uint8_t COLOR_MASK = 1 << 0;
		const uint8_t PIECE_TYPE_MASK = 1 << 1 | 1 << 2 | 1 << 3;
		const uint8_t IN_CHECK_MASK = 1 << 4;
		const uint8_t CASTLING_RIGHTS_MASK = 1 << 5 | 1 << 6;
		const uint8_t PIECE_HERE_MASK = 1 << 7;

		void setCastlingRights(int index, CastlingRightsBit rights);
		
		int kingIndex(ColorBit color) const;
		
		void makePiece(int index, PieceTypeBit type, ColorBit bit);
		char squareChar(int index) const;
		
		std::string bitToString(ColorBit color);

		friend std::ostream& operator<<(std::ostream& os, const Board& rhs);
	};
}