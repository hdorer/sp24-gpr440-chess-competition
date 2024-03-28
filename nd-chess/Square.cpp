#include "Square.h"


namespace NDChess {
	void Square::setInCheck(InCheckBit inCheck) {
		if (getPieceType() != PieceTypeBit::KING) {
			return;
		}

		data = (data & ~IN_CHECK_MASK) | (uint8_t)inCheck;
	}

	void Square::makePiece(PieceTypeBit type, ColorBit color) {
		uint8_t pieceHereVal = (uint8_t)PieceHereBit::YES;
		uint8_t typeVal = (uint8_t)type;
		uint8_t colorVal = (uint8_t)color;
		data = pieceHereVal | typeVal | colorVal;
	}

	std::ostream& operator<<(std::ostream& os, const Square& rhs) {
		char display = '.';

		if (rhs.isPieceHere()) {
			PieceTypeBit type = rhs.getPieceType();
			switch (type) {
			case PieceTypeBit::PAWN:
				display = 'p';
				break;
			case PieceTypeBit::KNIGHT:
				display = 'n';
				break;
			case PieceTypeBit::BISHOP:
				display = 'b';
				break;
			case PieceTypeBit::ROOK:
				display = 'r';
				break;
			case PieceTypeBit::QUEEN:
				display = 'q';
				break;
			case PieceTypeBit::KING:
				display = 'k';
				break;
			}

			if (rhs.getColor() == ColorBit::WHITE) {
				display -= 32;
			}
		}

		os << display;
		return os;
	}
}