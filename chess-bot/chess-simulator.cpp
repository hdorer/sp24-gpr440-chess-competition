#include "chess-simulator.h"
// disservin's lib. drop a star on his hard work!
// https://github.com/Disservin/chess-library
#include "chess.hpp"
#include <random>


BrainRot::BrainRot() {
	pieceValues = {
		{ chess::PieceGenType::PAWN, 1 },
		{ chess::PieceGenType::BISHOP, 3 },
		{ chess::PieceGenType::KNIGHT, 3 },
		{ chess::PieceGenType::ROOK, 5 },
		{ chess::PieceGenType::QUEEN, 9 },
		{ chess::PieceGenType::KING, 100 }
	};
}

chess::Move BrainRot::getNextMove(chess::Board& board) {
	// create your board based on the board string following the FEN notation
	// search for the best move using minimax / monte carlo tree search /
	// alpha-beta pruning / ... try to use nice heuristics to speed up the search
	// and have better results return the best move in UCI notation you will gain
	// extra points if you create your own board/move representation instead of
	// using the one provided by the library

	chess::Move move = makeMove(board);
	return move;
}

chess::Move BrainRot::getNextMove(std::string fen) {
	chess::Board board(fen);
	chess::Move move = makeMove(board);
	return move;
}

chess::Move BrainRot::makeMove(chess::Board& board) {
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