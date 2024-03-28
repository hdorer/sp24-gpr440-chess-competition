#include "Types.h"


namespace NDChess {
	std::string bitToString(ColorBit color) {
		switch (color) {
		case ColorBit::NOPIECE:
			return "None";
		case ColorBit::BLACK:
			return "Black";
		case ColorBit::WHITE:
			return "White";
		}
	}

	std::string bitToString(PieceTypeBit type) {
		switch (type) {
		case PieceTypeBit::NOPIECE:
			return "None";
		case PieceTypeBit::PAWN:
			return "Pawn";
		case PieceTypeBit::KNIGHT:
			return "Knight";
		case PieceTypeBit::BISHOP:
			return "Bishop";
		case PieceTypeBit::ROOK:
			return "Rook";
		case PieceTypeBit::QUEEN:
			return "Queen";
		case PieceTypeBit::KING:
			return "King";
		}
	}

	std::string bitToString(InCheckBit inCheck) {
		switch (inCheck) {
		case InCheckBit::NOTKING:
			return "Not the King";
		case InCheckBit::NO:
			return "Not in Check";
		case InCheckBit::YES:
			return "In Check";
		}
	}

	std::string bitToString(CastlingRightsBit rights) {
		switch (rights) {
		case CastlingRightsBit::NOTKING:
			return "Not the King";
		case CastlingRightsBit::SHORT_CASTLE:
			return "Short";
		case CastlingRightsBit::LONG_CASTLE:
			return "Long";
		case CastlingRightsBit::BOTH_CASTLES:
			return "Short + Long";
		}
	}
}