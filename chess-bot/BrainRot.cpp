#include "BrainRot.h"

// disservin's lib. drop a star on his hard work!
// https://github.com/Disservin/chess-library
#include "chess.hpp"
#include <random>
#include "Utils.h"


namespace ChessSimulator {
	BrainRot::BrainRot() {
		pieceValues = {
			{ chess::PieceType::PAWN, 1 },
			{ chess::PieceType::BISHOP, 3 },
			{ chess::PieceType::KNIGHT, 3 },
			{ chess::PieceType::ROOK, 5 },
			{ chess::PieceType::QUEEN, 9 },
			{ chess::PieceType::KING, 0 }
		};
		pieceSquareTables = {
			{
				chess::PieceType::PAWN, {
					{ chess::Color::WHITE, PieceSquareTables::whitePawn },
					{ chess::Color::BLACK, PieceSquareTables::blackPawn }
				}
			},
			{
				chess::PieceType::BISHOP, {
					{ chess::Color::WHITE, PieceSquareTables::whiteBishop },
					{ chess::Color::BLACK, PieceSquareTables::blackBishop }
				}
			},
			{
				chess::PieceType::KNIGHT, {
					{ chess::Color::WHITE, PieceSquareTables::whiteKnight },
					{ chess::Color::BLACK, PieceSquareTables::blackKnight }
				}
			},
			{
				chess::PieceType::ROOK, {
					{ chess::Color::WHITE, PieceSquareTables::whiteRook },
					{ chess::Color::BLACK, PieceSquareTables::blackRook }
				}
			},
			{
				chess::PieceType::QUEEN, {
					{ chess::Color::WHITE, PieceSquareTables::whiteQueen },
					{ chess::Color::BLACK, PieceSquareTables::blackQueen }
				}
			},
			{
				chess::PieceType::KING, {
					{ chess::Color::WHITE, PieceSquareTables::whiteKing },
					{ chess::Color::BLACK, PieceSquareTables::blackKing }
				}
			},
		};
	}

	chess::Color BrainRot::getSide() const {
		return side;
	}

	void BrainRot::setSide(bool side) {
		this->side = side ? chess::Color::WHITE : chess::Color::BLACK;
	}

	bool BrainRot::isWhite() const {
		return side == chess::Color::WHITE;
	}

	chess::Move BrainRot::getNextMove(chess::Board& board) {
		return getRandomMove(board);
	}

	void BrainRot::evaluatePosition(chess::Board& board, float& whiteScore, float& blackScore) {
		whiteScore = evaluateForSide(board, chess::Color::WHITE);
		blackScore = evaluateForSide(board, chess::Color::BLACK);
	}

	float BrainRot::evaluateForSide(chess::Board& board, chess::Color side) {
		int numPieces = 0;
		int material = 0;
		int positional = 0;
		int attackedPieces = 0;
		int notInCheck = 1;

		for (std::map<chess::PieceType, int>::iterator it = pieceValues.begin(); it != pieceValues.end(); ++it) {
			chess::Bitboard pieceBitboard = board.pieces(it->first, side);
			uint64_t pieceBits = pieceBitboard.getBits();

			uint64_t bitIncr = 1;
			int i = 0; // use this variable to prevent infinite loops by hard capping the loop at 64 iterations
			while (bitIncr <= pieceBits && i < 64) {
				if ((pieceBits & bitIncr) != 0) {
					numPieces++;
					material += pieceValues[it->first];
					positional += pieceSquareTables[it->first][side][i];

					if (board.isAttacked(chess::Square(i), oppositeColor(side))) {
						attackedPieces++;
					}
				}
				bitIncr <<= 1;
				i++;
			}
		}

		if (side != board.sideToMove()) {
			board.makeNullMove();
		}

		if (board.inCheck()) {
			notInCheck = 0;
		}

		if (side != board.sideToMove()) {
			board.unmakeNullMove();
		}

		return ((float)material / (float)BEST_POSSIBLE_MATERIAL) * materialWeight
			+ ((float)positional / (float)BEST_POSSIBLE_POSITIONAL_SCORE) * positionalWeight
			+ (((float)numPieces - (float)attackedPieces) / (float)numPieces) * attackWeight
			+ (float)notInCheck * checkWeight;
	}

	chess::Move BrainRot::getRandomMove(chess::Board& board) {
		chess::Movelist moves;
		chess::movegen::legalmoves(moves, board);
		if (moves.size() == 0) {
			return chess::Move();
		}

		// get random move
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> dist(0, moves.size() - 1);
		chess::Move move = moves[dist(gen)];
		return move;
	}
}