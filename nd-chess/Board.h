#pragma once

#include <iostream>
#include "Square.h"
#include "Types.h"


namespace NDChess {
	class Board {
	public:
		Square& operator[](int index) { return squares[index]; }

		void clear();
		void setPositionFromFen(std::string fen);
	private:
		static const int NUM_SQUARES = 64;
		Square squares[NUM_SQUARES];

		friend std::ostream& operator<<(std::ostream& os, const Board& rhs);
	};
}