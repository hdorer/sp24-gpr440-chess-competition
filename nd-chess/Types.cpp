#include "Types.h"


namespace NDChess {
	std::string bitToString(ColorBit color) {
		switch (color) {
		case ColorBit::NOPIECE:
			return "None";
		case ColorBit::BLACK:
			return "Black";
		case ColorBit::WHITE:
			return "White";
		}
	}

	std::string bitToString(PieceTypeBit type) {
		switch (type) {
		case PieceTypeBit::NOPIECE:
			return "None";
		case PieceTypeBit::PAWN:
			return "Pawn";
		case PieceTypeBit::KNIGHT:
			return "Knight";
		case PieceTypeBit::BISHOP:
			return "Bishop";
		case PieceTypeBit::ROOK:
			return "Rook";
		case PieceTypeBit::QUEEN:
			return "Queen";
		case PieceTypeBit::KING:
			return "King";
		}
	}

	std::string bitToString(InCheckBit inCheck) {
		switch (inCheck) {
		case InCheckBit::NOTKING:
			return "Not the King";
		case InCheckBit::NO:
			return "Not in Check";
		case InCheckBit::YES:
			return "In Check";
		}
	}

	std::string bitToString(CastlingRightsBit rights) {
		switch (rights) {
		case CastlingRightsBit::NOTKING:
			return "Not the King";
		case CastlingRightsBit::SHORT_CASTLE:
			return "Short";
		case CastlingRightsBit::LONG_CASTLE:
			return "Long";
		case CastlingRightsBit::BOTH_CASTLES:
			return "Short + Long";
		}
	}

	namespace PieceSquareTables {
		// Table value source: https://www.chessprogramming.org/PeSTO%27s_Evaluation_Function
		int blackPawn[64] = {
			0,   0,   0,   0,   0,   0,  0,   0,
			98, 134,  61,  95,  68, 126, 34, -11,
			-6,   7,  26,  31,  65,  56, 25, -20,
			-14,  13,   6,  21,  23,  12, 17, -23,
			-27,  -2,  -5,  12,  17,   6, 10, -25,
			-26,  -4,  -4, -10,   3,   3, 33, -12,
			-35,  -1, -20, -23, -15,  24, 38, -22,
			0,   0,   0,   0,   0,   0,  0,   0
		};
		int blackKnight[64] = {
			-167, -89, -34, -49,  61, -97, -15, -107,
			-73, -41,  72,  36,  23,  62,   7,  -17,
			-47,  60,  37,  65,  84, 129,  73,   44,
			-9,  17,  19,  53,  37,  69,  18,   22,
			-13,   4,  16,  13,  28,  19,  21,   -8,
			-23,  -9,  12,  10,  19,  17,  25,  -16,
			-29, -53, -12,  -3,  -1,  18, -14,  -19,
			-105, -21, -58, -33, -17, -28, -19,  -23,
		};
		int blackBishop[64] = {
			-29,   4, -82, -37, -25, -42,   7,  -8,
			-26,  16, -18, -13,  30,  59,  18, -47,
			-16,  37,  43,  40,  35,  50,  37,  -2,
			-4,   5,  19,  50,  37,  37,   7,  -2,
			-6,  13,  13,  26,  34,  12,  10,   4,
			0,  15,  15,  15,  14,  27,  18,  10,
			4,  15,  16,   0,   7,  21,  33,   1,
			-33,  -3, -14, -21, -13, -12, -39, -21,
		};
		int blackRook[64] = {
			32,  42,  32,  51, 63,  9,  31,  43,
			27,  32,  58,  62, 80, 67,  26,  44,
			-5,  19,  26,  36, 17, 45,  61,  16,
			-24, -11,   7,  26, 24, 35,  -8, -20,
			-36, -26, -12,  -1,  9, -7,   6, -23,
			-45, -25, -16, -17,  3,  0,  -5, -33,
			-44, -16, -20,  -9, -1, 11,  -6, -71,
			-19, -13,   1,  17, 16,  7, -37, -26,
		};
		int blackQueen[64] = {
			-28,   0,  29,  12,  59,  44,  43,  45,
			-24, -39,  -5,   1, -16,  57,  28,  54,
			-13, -17,   7,   8,  29,  56,  47,  57,
			-27, -27, -16, -16,  -1,  17,  -2,   1,
			-9, -26,  -9, -10,  -2,  -4,   3,  -3,
			-14,   2, -11,  -2,  -5,   2,  14,   5,
			-35,  -8,  11,   2,   8,  15,  -3,   1,
			-1, -18,  -9,  10, -15, -25, -31, -50,
		};
		int blackKing[64] = {
			65,  23,  16, -15, -56, -34,   2,  13,
			29,  -1, -20,  -7,  -8,  -4, -38, -29,
			-9,  24,   2, -16, -20,   6,  22, -22,
			-17, -20, -12, -27, -30, -25, -14, -36,
			-49,  -1, -27, -39, -46, -44, -33, -51,
			-14, -14, -22, -46, -44, -30, -15, -27,
			1,   7,  -8, -64, -43, -16,   9,   8,
			-15,  36,  12, -54,   8, -28,  24,  14,
		};
		
		int whitePawn[64] = {
			0, 0, 0, 0, 0, 0, 0, 0,
			-35, -1, -20, -23, -15, 24, 38, -22,
			-26, -4, -4, -10, 3, 3, 33, -12,
			-27, -2, -5, 12, 17, 6, 10, -25,
			-14, 13, 6, 21, 23, 12, 17, -23,
			-6, 7, 26, 31, 65, 56, 25, -20,
			98, 134, 61, 95, 68, 126, 34, -11,
			0, 0, 0, 0, 0, 0, 0, 0
		};

		int whiteKnight[64] = {
			-105, -21, -58, -33, -17, -28, -19, -23,
			-29, -53, -12, -3, -1, 18, -14, -19,
			-23, -9, 12, 10, 19, 17, 25, -16,
			-13, 4, 16, 13, 28, 19, 21, -8,
			-9, 17, 19, 53, 37, 69, 18, 22,
			-47, 60, 37, 65, 84, 129, 73, 44,
			-73, -41, 72, 36, 23, 62, 7, -17,
			-167, -89, -34, -49, 61, -97, -15, -107
		};

		int whiteBishop[64] = {
			-33, -3, -14, -21, -13, -12, -39, -21,
			4, 15, 16, 0, 7, 21, 33, 1,
			0, 15, 15, 15, 14, 27, 18, 10,
			-6, 13, 13, 26, 34, 12, 10, 4,
			-4, 5, 19, 50, 37, 37, 7, -2,
			-16, 37, 43, 40, 35, 50, 37, -2,
			-26, 16, -18, -13, 30, 59, 18, -47,
			-29, 4, -82, -37, -25, -42, 7, -8
		};

		int whiteRook[64] = {
			-19, -13, 1, 17, 16, 7, -37, -26,
			-44, -16, -20, -9, -1, 11, -6, -71,
			-45, -25, -16, -17, 3, 0, -5, -33,
			-36, -26, -12, -1, 9, -7, 6, -23,
			-24, -11, 7, 26, 24, 35, -8, -20,
			-5, 19, 26, 36, 17, 45, 61, 16,
			27, 32, 58, 62, 80, 67, 26, 44,
			32, 42, 32, 51, 63, 9, 31, 43
		};

		int whiteQueen[64] = {
			-1, -18, -9, 10, -15, -25, -31, -50,
			-35, -8, 11, 2, 8, 15, -3, 1,
			-14, 2, -11, -2, -5, 2, 14, 5,
			-9, -26, -9, -10, -2, -4, 3, -3,
			-27, -27, -16, -16, -1, 17, -2, 1,
			-13, -17, 7, 8, 29, 56, 47, 57,
			-24, -39, -5, 1, -16, 57, 28, 54,
			-28, 0, 29, 12, 59, 44, 43, 45
		};

		int whiteKing[64] = {
			-15, 36, 12, -54, 8, -28, 24, 14,
			1, 7, -8, -64, -43, -16, 9, 8,
			-14, -14, -22, -46, -44, -30, -15, -27,
			-49, -1, -27, -39, -46, -44, -33, -51,
			-17, -20, -12, -27, -30, -25, -14, -36,
			-9, 24, 2, -16, -20, 6, 22, -22,
			29, -1, -20, -7, -8, -4, -38, -29,
			65, 23, 16, -15, -56, -34, 2, 13
		};
	}
}