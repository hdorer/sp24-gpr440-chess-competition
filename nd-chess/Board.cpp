#include "Board.h"


namespace NDChess {
	Board::Board() : sideToMove(ColorBit::WHITE), squares{
		135, 131, 133, 137, 139, 133, 131, 135,
		129, 129, 129, 129, 129, 129, 129, 129,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0,
		128, 128, 128, 128, 128, 128, 128, 128,
		134, 130, 132, 136, 138, 132, 130, 134
	} {	}
	
	void Board::clear() {
		for (int i = 0; i < NUM_SQUARES; i++) {
			clear(i);
		}
	}

	void Board::clear(int index) {
		squares[index] = 0;
	}
	
	void Board::setPositionFromFen(std::string fen) {
		int state = 0;
		int rank = 7;
		int file = 0;
		char* data = fen.data();		

		clear();

		int i = 0;
		while (i < fen.size()) {
			char current = data[i];

			switch (state) {
			case 0:
				if (data[i] >= 48 && data[i] <= 57) {
					file += data[i] - 48;
				} else {
					switch (data[i]) {
					case '/':
						rank--;
						file = 0;
						break;
					case 'r':
						makePiece(rank * 8 + file, PieceTypeBit::ROOK, ColorBit::BLACK);
						file++;
						break;
					case 'n':
						makePiece(rank * 8 + file, PieceTypeBit::KNIGHT, ColorBit::BLACK);
						file++;
						break;
					case 'b':
						makePiece(rank * 8 + file, PieceTypeBit::BISHOP, ColorBit::BLACK);
						file++;
						break;
					case 'q':
						makePiece(rank * 8 + file, PieceTypeBit::QUEEN, ColorBit::BLACK);
						file++;
						break;
					case 'k':
						makePiece(rank * 8 + file, PieceTypeBit::KING, ColorBit::BLACK);
						file++;
						break;
					case 'p':
						makePiece(rank * 8 + file, PieceTypeBit::PAWN, ColorBit::BLACK);
						file++;
						break;
					case 'R':
						makePiece(rank * 8 + file, PieceTypeBit::ROOK, ColorBit::WHITE);
						file++;
						break;
					case 'N':
						makePiece(rank * 8 + file, PieceTypeBit::KNIGHT, ColorBit::WHITE);
						file++;
						break;
					case 'B':
						makePiece(rank * 8 + file, PieceTypeBit::BISHOP, ColorBit::WHITE);
						file++;
						break;
					case 'Q':
						makePiece(rank * 8 + file, PieceTypeBit::QUEEN, ColorBit::WHITE);
						file++;
						break;
					case 'K':
						makePiece(rank * 8 + file, PieceTypeBit::KING, ColorBit::WHITE);
						file++;
						break;
					case 'P':
						makePiece(rank * 8 + file, PieceTypeBit::PAWN, ColorBit::WHITE);
						file++;
						break;
					case ' ':
						state++;
						break;
					}
				}

				break;
			case 1:
				
			case 2:
				break;
			}

			i++;
		}
	}
	
	void Board::printRawView() {
		std::cout << "(Note: Ranks are drawn in reverse order in raw view)" << std::endl;
		for (int i = 0; i < NUM_SQUARES; i++) {
			std::cout << (int)(squares[i]) << "|";
			if (i != 0 && i % 8 == 7) {
				std::cout << std::endl;
			}
		}
	}

	ColorBit Board::getColor(int index) const {
		if (!isPieceHere(index)) {
			return ColorBit::NOPIECE;
		}
		return (ColorBit)(squares[index] & COLOR_MASK);
	}

	PieceTypeBit Board::getPieceType(int index) const {
		if (!isPieceHere(index)) {
			return PieceTypeBit::NOPIECE;
		}
		return (PieceTypeBit)(squares[index] & PIECE_TYPE_MASK);
	}

	void Board::makePiece(int index, PieceTypeBit type, ColorBit color) {
		uint8_t pieceHereVal = (uint8_t)PieceHereBit::YES;
		uint8_t typeVal = (uint8_t)type;
		uint8_t colorVal = (uint8_t)color;
		squares[index] = pieceHereVal | typeVal | colorVal;
	}

	char Board::squareChar(int index) const {
		char display = '.';

		if (isPieceHere(index)) {
			PieceTypeBit type = getPieceType(index);
			switch (type) {
			case PieceTypeBit::PAWN:
				display = 'p';
				break;
			case PieceTypeBit::KNIGHT:
				display = 'n';
				break;
			case PieceTypeBit::BISHOP:
				display = 'b';
				break;
			case PieceTypeBit::ROOK:
				display = 'r';
				break;
			case PieceTypeBit::QUEEN:
				display = 'q';
				break;
			case PieceTypeBit::KING:
				display = 'k';
				break;
			}

			if (getColor(index) == ColorBit::WHITE) {
				display -= 32;
			}
		}

		return display;
	}

	std::ostream& operator<<(std::ostream& os, const Board& rhs) {
		int rank = 7;
		int file = 0;
		for (int i = 0; i < Board::NUM_SQUARES; i++) {
			os << rhs.squareChar(rank * 8 + file);
			file++;
			if (i != 0 && i % 8 == 7) {
				os << std::endl;
				rank--;
				file = 0;
			}
		}
		return os;
	}
}