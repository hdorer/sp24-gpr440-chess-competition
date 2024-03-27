#include "PGNBuilder.h"


void PGNBuilder::addMove(chess::Board& board, chess::Move& move) {
	std::string moveStr = chess::uci::moveToSan(board, move);

	if (!isFirstMove()) {
		pgnString << " ";
	}

	if (white) {
		pgnString << turn << ". ";
	}

	pgnString << moveStr;

	if (!white) {
		turn++;
	}
	white = !white;
}

std::ostream& operator<<(std::ostream& os, const PGNBuilder& rhs) {
	os << rhs.pgnString.str();
	return os;
}

bool PGNBuilder::isFirstMove() {
	return turn == 1 && white;
}