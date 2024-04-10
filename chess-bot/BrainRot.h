#pragma once

#include <string>
#include <chess.hpp>
#include <map>

class BrainRot {
public:
	BrainRot();

	chess::Color getSide() const;
	void setSide(bool side);

	bool isWhite() const;
	chess::Move getNextMove(chess::Board& board);

	float evaluatePosition(chess::Board& board);

private:
	std::map<chess::PieceType, int> pieceValues;
	chess::Color side;
};