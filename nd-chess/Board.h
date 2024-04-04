#pragma once

#include <iostream>
#include <string>
#include "Types.h"


namespace NDChess {
	class Board {
	public:
		static const int NUM_SQUARES = 64;

		Board();

		void clear();
		void clear(int index);
		void setPositionFromFen(std::string fen);
		
		std::string rawView();
		std::string pieceToString(int index);

		int material(ColorBit color);
		void evaluatePosition(float& whiteScore, float& blackScore);

		bool isPieceHere(int index) const;
		ColorBit getColor(int index) const;
		PieceTypeBit getPieceType(int index) const;
		InCheckBit getInCheck(int index) const;
		CastlingRightsBit getCastlingRights(int index) const;
	private:
		uint8_t squares[NUM_SQUARES];

		ColorBit sideToMove;
	
		const uint8_t COLOR_MASK = 1;
		const uint8_t PIECE_TYPE_MASK = 14;
		const uint8_t IN_CHECK_MASK = 16;
		const uint8_t CASTLING_RIGHTS_MASK = 96;
		const uint8_t PIECE_HERE_MASK = 128;

		void setCastlingRights(int index, CastlingRightsBit rights);
		
		int kingIndex(ColorBit color) const;
		
		void makePiece(int index, PieceTypeBit type, ColorBit bit);
		char squareChar(int index) const;

		friend std::ostream& operator<<(std::ostream& os, const Board& rhs);
	};
}