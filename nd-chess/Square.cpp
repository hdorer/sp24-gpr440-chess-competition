#include "Square.h"


namespace NDChess {
	void Square::setInCheck(InCheckBit inCheck) {
		if (getPieceType() != PieceTypeBit::KING) {
			return;
		}

		data = (data & ~IN_CHECK_MASK) | (uint8_t)inCheck;
	}

	std::ostream& operator<<(std::ostream& os, const Square& rhs) {
		char display = '.';

		if (rhs.isPieceHere()) {
			switch (rhs.getPieceType()) {
			case PieceTypeBit::PAWN:
				display = 'p';
				break;
			case PieceTypeBit::KNIGHT:
				display = 'n';
				break;
			case PieceTypeBit::BISHOP:
				display = 'b';
				break;
			case PieceTypeBit::QUEEN:
				display = 'b';
				break;
			case PieceTypeBit::KING:
				display = 'k';
			}

			if (rhs.getColor() == ColorBit::BLACK) {
				display -= 32;
			}
		}

		os << display;
		return os;
	}
}