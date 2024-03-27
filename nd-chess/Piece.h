#pragma once

#include <stdint.h>

namespace NDChess {
	class Piece {
	public:
		enum ColorBit : uint8_t{
			BLACK = 0,
			WHITE = 1
		};

		enum PieceTypeBit : uint8_t {
			PAWN = 0,
			KNIGHT = 2,
			BISHOP = 4,
			ROOK = 6,
			QUEEN = 8,
			KING = 10,
			EN_PASSANT_PAWN = 12
		};

		// i guess i'm not going to have classes for each piece
		enum InCheckBit : uint8_t {
			NO = 0,
			YES = 16
		};

		ColorBit getColor() const;
		PieceTypeBit getPieceType() const;
		InCheckBit getInCheck() const;
		void setColor(ColorBit color);
		void setPieceType(PieceTypeBit type);
		void setInCheck(InCheckBit inCheck);
	private:
		uint8_t data;

		const uint8_t COLOR_MASK = 1 << 1;
		const uint8_t PIECE_TYPE_MASK = 1 << 2 | 1 << 3 | 1 << 4;
		const uint8_t IN_CHECK_MASK = 1 << 5;
	};
}