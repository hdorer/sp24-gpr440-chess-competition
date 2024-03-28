#include "Board.h"


namespace NDChess {
	void Board::clear() {
		for (int i = 0; i < NUM_SQUARES; i++) {
			squares[i].clear();
		}
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
						squares[rank * 8 + file].makePiece(PieceTypeBit::ROOK, ColorBit::BLACK);
						file++;
						break;
					case 'n':
						squares[rank * 8 + file].makePiece(PieceTypeBit::KNIGHT, ColorBit::BLACK);
						file++;
						break;
					case 'b':
						squares[rank * 8 + file].makePiece(PieceTypeBit::BISHOP, ColorBit::BLACK);
						file++;
						break;
					case 'q':
						squares[rank * 8 + file].makePiece(PieceTypeBit::QUEEN, ColorBit::BLACK);
						file++;
						break;
					case 'k':
						squares[rank * 8 + file].makePiece(PieceTypeBit::KING, ColorBit::BLACK);
						file++;
						break;
					case 'p':
						squares[rank * 8 + file].makePiece(PieceTypeBit::PAWN, ColorBit::BLACK);
						file++;
						break;
					case 'R':
						squares[rank * 8 + file].makePiece(PieceTypeBit::ROOK, ColorBit::WHITE);
						file++;
						break;
					case 'N':
						squares[rank * 8 + file].makePiece(PieceTypeBit::KNIGHT, ColorBit::WHITE);
						file++;
						break;
					case 'B':
						squares[rank * 8 + file].makePiece(PieceTypeBit::BISHOP, ColorBit::WHITE);
						file++;
						break;
					case 'Q':
						squares[rank * 8 + file].makePiece(PieceTypeBit::QUEEN, ColorBit::WHITE);
						file++;
						break;
					case 'K':
						squares[rank * 8 + file].makePiece(PieceTypeBit::KING, ColorBit::WHITE);
						file++;
						break;
					case 'P':
						squares[rank * 8 + file].makePiece(PieceTypeBit::PAWN, ColorBit::WHITE);
						file++;
						break;
					case ' ':
						state++;
						break;
					}
				}

				break;
			case 1:
				std::cout << "Board finished!" << std::endl;
				state++;
				break;
			case 2:
				break;
			}

			i++;
		}
	}

	std::ostream& operator<<(std::ostream& os, const Board& rhs) {
		int rank = 7;
		int file = 0;
		for (int i = 0; i < Board::NUM_SQUARES; i++) {
			os << rhs.squares[rank * 8 + file];
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