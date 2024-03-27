#pragma once

#include <iostream>
#include <stdint.h>


namespace NDChess {
	class Square {
	public:
		enum class ColorBit : uint8_t{
			BLACK = 0,
			WHITE = 1
		};

		enum class PieceTypeBit : uint8_t {
			PAWN = 0,
			KNIGHT = 2,
			BISHOP = 4,
			ROOK = 6,
			QUEEN = 8,
			KING = 10,
			EN_PASSANT_PAWN = 12
		};

		// i guess i'm not going to have classes for each piece
		enum class InCheckBit : uint8_t {
			NO = 0,
			YES = 16
		};

		enum class PieceHereBit: uint8_t{
			NO = 0,
			YES = 128
		};

		Square() : data(128) { }

		ColorBit getColor() const;
		PieceTypeBit getPieceType() const;
		InCheckBit getInCheck() const;
		bool isPieceHere() const;
		void setColor(ColorBit color);
		void setPieceType(PieceTypeBit type);
		void setInCheck(InCheckBit inCheck);
		void setPieceHere(PieceHereBit pieceHere);

		friend std::ostream& operator<<(std::ostream& os, Square& rhs);
	private:
		uint8_t data;

		const uint8_t COLOR_MASK = 1 << 0;
		const uint8_t PIECE_TYPE_MASK = 1 << 1 | 1 << 2 | 1 << 3;
		const uint8_t IN_CHECK_MASK = 1 << 5;
		const uint8_t PIECE_HERE_MASK = 1 << 7;
	};
}