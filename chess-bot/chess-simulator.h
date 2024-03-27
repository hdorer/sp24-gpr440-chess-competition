#pragma once
#include <string>
#include <chess.hpp>
#include <map>

class BrainRot {
public:
	BrainRot();

	chess::Color getSide() const;
	void setSide(bool side);

	bool isWhite();
	chess::Move getNextMove(chess::Board& board);

private:
	std::map<chess::PieceGenType, int> pieceValues;
	chess::Color side;
};