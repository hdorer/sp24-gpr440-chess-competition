#pragma once

#include <stdint.h>
#include <string>


namespace NDChess {
	enum class ColorBit : uint8_t {
		NOPIECE = -1,
		BLACK = 0,
		WHITE = 1
	};

	std::string bitToString(ColorBit color);

	enum class PieceTypeBit : uint8_t {
		NOPIECE = -1,
		PAWN = 0,
		KNIGHT = 2,
		BISHOP = 4,
		ROOK = 6,
		QUEEN = 8,
		KING = 10,
		EN_PASSANT_PAWN = 12
	};

	std::string bitToString(PieceTypeBit type);

	enum class InCheckBit : uint8_t {
		NOTKING = -1,
		NO = 0,
		YES = 16
	};

	std::string bitToString(InCheckBit inCheck);

	enum class CastlingRightsBit: uint8_t{
		NOTKING = -1,
		NO_CASTLE = 0,
		SHORT_CASTLE = 32,
		LONG_CASTLE = 64,
		BOTH_CASTLES = 96
	};

	std::string bitToString(CastlingRightsBit rights);
}