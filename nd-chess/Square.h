#pragma once

#include <iostream>
#include <stdint.h>
#include "Types.h"


namespace NDChess {
	class Square {
	public:
		Square() : data(128) { }

		ColorBit getColor() const { return (ColorBit)(data & COLOR_MASK); }
		PieceTypeBit getPieceType() const { return (PieceTypeBit)(data & PIECE_TYPE_MASK); }
		InCheckBit getInCheck() const { return (InCheckBit)(data & IN_CHECK_MASK); }
		bool isPieceHere() const { return (bool)(data & PIECE_HERE_MASK); }
		void setColor(ColorBit color) { data = (data & ~COLOR_MASK) | (uint8_t)color; }
		void setPieceType(PieceTypeBit type) { data = (data & ~PIECE_TYPE_MASK) | (uint8_t)type; }
		void setInCheck(InCheckBit inCheck);
		void setPieceHere(PieceHereBit pieceHere) { data - (data & ~PIECE_HERE_MASK) | (uint8_t)pieceHere; }

		friend std::ostream& operator<<(std::ostream& os, const Square& rhs);
	private:
		uint8_t data;

		const uint8_t COLOR_MASK = 1 << 0;
		const uint8_t PIECE_TYPE_MASK = 1 << 1 | 1 << 2 | 1 << 3;
		const uint8_t IN_CHECK_MASK = 1 << 5;
		const uint8_t PIECE_HERE_MASK = 1 << 7;
	};
}