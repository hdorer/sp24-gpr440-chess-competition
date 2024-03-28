#include "Board.h"


namespace NDChess {
	std::ostream& operator<<(std::ostream& os, const Board& rhs) {
		for (int i = 0; i < Board::NUM_SQUARES; i++) {
			os << rhs.squares[i];
			if (i != 0 && i % 8 == 0) {
				os << std::endl;
			}
		}
		return os;
	}
}