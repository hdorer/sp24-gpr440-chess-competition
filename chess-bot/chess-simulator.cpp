#include "chess-simulator.h"

// disservin's lib. drop a star on his hard work!
// https://github.com/Disservin/chess-library
#include "chess.hpp"
#include <random>


BrainRot::BrainRot() {
	pieceValues = {
		{ chess::PieceType::PAWN, 1 },
		{ chess::PieceType::BISHOP, 3 },
		{ chess::PieceType::KNIGHT, 3 },
		{ chess::PieceType::ROOK, 5 },
		{ chess::PieceType::QUEEN, 9 },
		{ chess::PieceType::KING, 0 }
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
	// create your board based on the board string following the FEN notation
	// search for the best move using minimax / monte carlo tree search /
	// alpha-beta pruning / ... try to use nice heuristics to speed up the search
	// and have better results return the best move in UCI notation you will gain
	// extra points if you create your own board/move representation instead of
	// using the one provided by the library

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

float BrainRot::evaluatePosition(chess::Board& board) {
	float material = 0;
	for (std::map<chess::PieceType, int>::iterator it = pieceValues.begin(); it != pieceValues.end(); ++it) {
		chess::Bitboard pieceBitboard = board.pieces(it->first, side);
		uint64_t pieceBits = pieceBitboard.getBits();

		uint64_t bitIncr = 1;
		int numPieces = 0;
		int i = 0; // use this variable to prevent infinite loops by hard capping the loop at 64 iterations
		while (bitIncr <= pieceBits && i < 64) {
			numPieces += (pieceBits & bitIncr) != 0;
			bitIncr <<= 1;
			i++;
		}

		material += (float)(numPieces * it->second);
	}

	return material;
}