#include "Move.h"

#include "Board.h"


namespace NDChess {
	std::vector<Move> MoveRules::pawn(const Board* board, int index, ColorBit color, bool attacksOnly) {
		std::vector<Move> result;
		int moveDirection = board->getColor(index) == ColorBit::WHITE ? 1 : -1;

		if (!attacksOnly) {
			// pawns can move one space forward
			int oneForwardIndex = index + 8 * moveDirection;
			if (pawnMove(result, board, index, oneForwardIndex)) {
				int startRank = index / 8;
				if (startRank == board->pawnRank(color)) {
					int twoForwardIndex = oneForwardIndex + 8 * moveDirection;
					pawnMove(result, board, index, twoForwardIndex);
				}
			}
		}

		int diagonalLeftIndex = index + 7 * moveDirection; // left relative to the direction the pawn is facing I guess lol
		pawnAttack(result, board, index, diagonalLeftIndex, color);

		int diagonalRightIndex = index + 9 * moveDirection;
		pawnAttack(result, board, index, diagonalRightIndex, color);

		return result;
	}

	std::vector<Move> MoveRules::knight(const Board* board, int index, ColorBit color) {
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

	std::vector<Move> MoveRules::bishop(const Board* board, int index, ColorBit color) {
		return bishop(board, index, color);
	}

	std::vector<Move> MoveRules::rook(const Board* board, int index, ColorBit color) {
		return rook(board, index, color, 8);
	}

	std::vector<Move> MoveRules::queen(const Board* board, int index, ColorBit color) {
		return queen(board, index, color, 8);
	}

	std::vector<Move> MoveRules::king(const Board* board, int index, ColorBit color) {
		return queen(board, index, color, 1);
	}

	std::vector<Move> MoveRules::bishop(const Board* board, int index, ColorBit color, int distanceCap) {
		std::vector<Move> result;

		lineMove(result, board, index, -9, color, distanceCap);
		lineMove(result, board, index, -7, color, distanceCap);
		lineMove(result, board, index, 7, color, distanceCap);
		lineMove(result, board, index, 9, color, distanceCap);

		return result;
	}

	std::vector<Move> MoveRules::rook(const Board* board, int index, ColorBit color, int distanceCap) {
		std::vector<Move> result;

		lineMove(result, board, index, -1, color, distanceCap);
		lineMove(result, board, index, 1, color, distanceCap);
		lineMove(result, board, index, -8, color, distanceCap);
		lineMove(result, board, index, 8, color, distanceCap);

		return result;
	}

	std::vector<Move> MoveRules::queen(const Board* board, int index, ColorBit color, int distanceCap) {
		std::vector<Move> straightMoves = rook(board, index, color, distanceCap);
		std::vector<Move> diagonalMoves = bishop(board, index, color, distanceCap);

		std::vector<Move> result;
		result.reserve(straightMoves.size() + diagonalMoves.size());
		result.insert(result.end(), straightMoves.begin(), straightMoves.end());
		result.insert(result.end(), diagonalMoves.begin(), diagonalMoves.end());

		return result;
	}

	bool MoveRules::pawnMove(std::vector<Move>& moveList, const Board* board, int startIndex, int endIndex) {
		if (!board->isPieceHere(endIndex)) {
			Move newMove(startIndex, endIndex);
			moveList.push_back(newMove);
			return true;
		}
		return false;
	}

	bool MoveRules::pawnAttack(std::vector<Move>& moveList, const Board* board, int startIndex, int endIndex, ColorBit color) {
		if (board->isOpponentPieceHere(endIndex, color)) {
			Move newMove(startIndex, endIndex);
			moveList.push_back(newMove);
			return true;
		}
		return false;
	}

	void MoveRules::lineMove(std::vector<Move>& moveList, const Board* board, int startIndex, int increment, ColorBit color, int distanceCap) {
		int currentIndex = startIndex;
		int currentRank;
		int currentFile;
		
		for (int i = 0; i < distanceCap; i++) {
			currentIndex += increment;
			currentRank = currentIndex / 8;
			currentFile = currentIndex % 8;

			if (currentRank > 0 || currentRank < 7 || currentFile > 0 || currentFile < 7) {
				return;
			}

			Move newMove(startIndex, currentIndex);

			if (board->isOpponentPieceHere(currentIndex, color)) {
				moveList.push_back(newMove);
				return;
			}
			if (board->isPieceHere(currentIndex)) {
				return;
			}
			moveList.push_back(newMove);
		}
	}
}