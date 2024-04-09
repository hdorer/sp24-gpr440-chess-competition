#pragma once

#include <iostream>
#include "Move.h"
#include <string>
#include "Types.h"
#include <vector>


namespace NDChess {
	class Board {
	public:
		static const int NUM_SQUARES = 64;

		Board();

		void clear();
		void clear(int index);
		void setPositionFromFen(std::string fen);
		
		std::string rawView() const;
		std::string squareName(int index) const;
		char squareChar(int index) const;
		std::string pieceInfo(int index) const;

		int material(ColorBit color) const;
		std::vector<Move> legalMoves(ColorBit color, bool pawnAttacksOnly = false) const;
		void evaluatePosition(int& whiteScore, int& blackScore) const;

		bool isPieceHere(int index) const;
		ColorBit getColor(int index) const;
		PieceTypeBit getPieceType(int index) const;
		InCheckBit getInCheck(int index) const;
		CastlingRightsBit getCastlingRights(int index) const;

		bool isOpponentPieceHere(int index, ColorBit color) const;
		int pawnRank(ColorBit color) const;
	private:
		uint8_t squares[NUM_SQUARES];

		ColorBit sideToMove;
	
		const uint8_t COLOR_MASK = 1;
		const uint8_t PIECE_TYPE_MASK = 14;
		const uint8_t IN_CHECK_MASK = 16;
		const uint8_t CASTLING_RIGHTS_MASK = 96;
		const uint8_t PIECE_HERE_MASK = 128;

		int kingIndex(ColorBit color) const;
		std::vector<Move> moveRulesOfSquare(int index, ColorBit color, bool pawnAttacksOnly = false) const;
		
		void makePiece(int index, PieceTypeBit type, ColorBit bit);
		void setCastlingRights(int index, CastlingRightsBit rights);

		friend std::ostream& operator<<(std::ostream& os, const Board& rhs);
	};
}