#include "Move.h"

#include "Board.h"


namespace NDChess {
	std::vector<Move> MoveRules::pawn(Board* board, int index, ColorBit color) {
		std::vector<Move> result;
		int moveDirection = board->getColor(index) == ColorBit::WHITE ? 1 : -1;

		// pawns can move one space forward
		int oneForwardIndex = index + 8 * moveDirection;
		if (pawnMove(result, board, index, oneForwardIndex)) {
			int startRank = index / 8;
			if (startRank == board->pawnRank(color)) {
				int twoForwardIndex = oneForwardIndex + 8 * moveDirection;
				pawnMove(result, board, index, twoForwardIndex);
			}
		}

		int diagonalLeftIndex = index + 7 * moveDirection; // left relative to the direction the pawn is facing I guess lol
		pawnAttack(result, board, index, diagonalLeftIndex, color);

		int diagonalRightIndex = index + 9 * moveDirection;
		pawnAttack(result, board, index, diagonalRightIndex, color);

		return result;
	}

	std::vector<Move> MoveRules::knight(Board* board, int index, ColorBit color) {
		std::vector<Move> result;
		int relativeIndices[] = { -15, -17, -6, -10, 6, 10, 15, 17 };

		for (int i = 0; i < 8; i++) {
			int endIndex = relativeIndices[i];
			if (!board->isPieceHere(endIndex)) {
				Move newMove(index, endIndex);
				result.push_back(newMove);
				continue;
			}

			if (board->isOpponentPieceHere(index, color)) {
				Move newMove(index, endIndex);
				result.push_back(newMove);
			}
		}

		return result;
	}

	bool MoveRules::pawnMove(std::vector<Move>& moveList, Board* board, int startIndex, int endIndex) {
		if (!board->isPieceHere(endIndex)) {
			Move newMove(startIndex, endIndex);
			moveList.push_back(newMove);
			return true;
		}
		return false;
	}

	bool MoveRules::pawnAttack(std::vector<Move>& moveList, Board* board, int startIndex, int endIndex, ColorBit color) {
		if (board->isOpponentPieceHere(endIndex, color)) {
			Move newMove(startIndex, endIndex);
			moveList.push_back(newMove);
		}
	}
}