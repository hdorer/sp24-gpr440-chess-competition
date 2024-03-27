#pragma once
#include <string>
#include <chess.hpp>
#include <map>

class BrainRot {
public:
	BrainRot();
	chess::Move getNextMove(chess::Board& board);

private:
	std::map<chess::PieceGenType, int> pieceValues;
	chess::Move makeMove(chess::Board& board);
};