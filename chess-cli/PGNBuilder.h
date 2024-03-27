#pragma once

#include <chess.hpp>
#include <iostream>
#include <string>


class PGNBuilder {
public:
	PGNBuilder() : turn(1), white(true) { }

	void addMove(chess::Board& board, chess::Move& move);

	friend std::ostream& operator<<(std::ostream& os, const PGNBuilder& rhs);

private:
	std::stringstream pgnString;
	int turn;
	bool white;

	bool isFirstMove();
};