#pragma once
#include <string>
#include <chess.hpp>
#include <map>

class BrainRot {
public:
	BrainRot();
	std::string getNextMove(std::string fen);

private:
	std::map<chess::PieceGenType, int> pieceValues;
};