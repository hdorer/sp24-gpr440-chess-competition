#include "Move.h"

#include "Board.h"
#include <sstream>


namespace NDChess {
	std::string Move::toString(const Board* board) const {
		std::stringstream result;

		result << board->squareChar(startIndex);
		result << board->squareName(startIndex);
		result << board->squareName(endIndex);

		return result.str();
	}
	
	std::vector<Move> MoveRules::pawn(const Board* board, int index, bool attacksOnly) {
		std::vector<Move> result;
		int moveDirection = board->getColor(index) == ColorBit::WHITE ? 1 : -1;

		if (!attacksOnly) {
			// pawns can move one space forward
			int oneForwardIndex = index + 8 * moveDirection;
			if (pawnMove(result, board, index, oneForwardIndex)) {
				int startRank = index / 8;
				if (startRank == board->pawnRank(board->getColor(index))) {
					int twoForwardIndex = oneForwardIndex + 8 * moveDirection;
					pawnMove(result, board, index, twoForwardIndex);
				}
			}
		}

		int diagonalLeftIndex = index + 7 * moveDirection; // left relative to the direction the pawn is facing I guess lol
		pawnAttack(result, board, index, diagonalLeftIndex);

		int diagonalRightIndex = index + 9 * moveDirection;
		pawnAttack(result, board, index, diagonalRightIndex);

		return result;
	}

	std::vector<Move> MoveRules::knight(const Board* board, int index) {
		std::vector<Move> result;
		int relativeIndices[] = { -15, -17, -6, -10, 6, 10, 15, 17 };

		for (int i = 0; i < 8; i++) {
			int endIndex = relativeIndices[i];
			if (!board->isPieceHere(endIndex)) {
				Move newMove(board->getPieceType(index), board->getColor(index), index, endIndex, board);
				result.push_back(newMove);
				continue;
			}

			if (board->isOpponentPieceHere(index, board->getColor(index))) {
				Move newMove(board->getPieceType(index), board->getColor(index), index, endIndex, board);
				result.push_back(newMove);
			}
		}

		return result;
	}

	std::vector<Move> MoveRules::bishop(const Board* board, int index) {
		return bishop(board, index, 8);
	}

	std::vector<Move> MoveRules::rook(const Board* board, int index) {
		return rook(board, index, 8);
	}

	std::vector<Move> MoveRules::queen(const Board* board, int index) {
		return queen(board, index, 8);
	}

	std::vector<Move> MoveRules::king(const Board* board, int index) {
		return queen(board, index, 1);
	}

	std::vector<Move> MoveRules::bishop(const Board* board, int index, int distanceCap) {
		std::vector<Move> result;

		lineMove(result, board, index, -9, distanceCap);
		lineMove(result, board, index, -7, distanceCap);
		lineMove(result, board, index, 7, distanceCap);
		lineMove(result, board, index, 9, distanceCap);

		return result;
	}

	std::vector<Move> MoveRules::rook(const Board* board, int index, int distanceCap) {
		std::vector<Move> result;

		lineMove(result, board, index, -1, distanceCap);
		lineMove(result, board, index, 1, distanceCap);
		lineMove(result, board, index, -8, distanceCap);
		lineMove(result, board, index, 8, distanceCap);

		return result;
	}

	std::vector<Move> MoveRules::queen(const Board* board, int index, int distanceCap) {
		std::vector<Move> straightMoves = rook(board, index, distanceCap);
		std::vector<Move> diagonalMoves = bishop(board, index, distanceCap);

		std::vector<Move> result;
		result.reserve(straightMoves.size() + diagonalMoves.size());
		result.insert(result.end(), straightMoves.begin(), straightMoves.end());
		result.insert(result.end(), diagonalMoves.begin(), diagonalMoves.end());

		return result;
	}

	bool MoveRules::pawnMove(std::vector<Move>& moveList, const Board* board, int startIndex, int endIndex) {
		if (!board->isPieceHere(endIndex)) {
			Move newMove(board->getPieceType(startIndex), board->getColor(startIndex), startIndex, endIndex, board);
			moveList.push_back(newMove);
			return true;
		}
		return false;
	}

	bool MoveRules::pawnAttack(std::vector<Move>& moveList, const Board* board, int startIndex, int endIndex) {
		if (board->isOpponentPieceHere(endIndex, board->getColor(startIndex))) {
			Move newMove(board->getPieceType(startIndex), board->getColor(startIndex), startIndex, endIndex, board);
			moveList.push_back(newMove);
			return true;
		}
		return false;
	}

	void MoveRules::lineMove(std::vector<Move>& moveList, const Board* board, int startIndex, int increment, int distanceCap) {
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

			Move newMove(board->getPieceType(startIndex), board->getColor(startIndex), startIndex, currentIndex, board);

			if (board->isOpponentPieceHere(currentIndex, board->getColor(startIndex))) {
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