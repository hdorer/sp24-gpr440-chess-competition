#pragma once

#include <stdint.h>


namespace NDChess {
	enum class ColorBit : uint8_t {
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

	enum class PieceHereBit : uint8_t {
		NO = 0,
		YES = 128
	};
}