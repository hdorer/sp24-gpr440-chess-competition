#include "Board.h"

#include <sstream>


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
	} { }
	
	void Board::clear() {
		for (int i = 0; i < NUM_SQUARES; i++) {
			clear(i);
		}
	}

	void Board::clear(int index) {
		if (index < 0 || index >= NUM_SQUARES) {
			return;
		}

		squares[index] = 0;
	}
	
	void Board::setPositionFromFen(std::string fen) {
		int state = 0;
		int rank = 7;
		int file = 0;
		uint8_t whiteCastlingRights = 0;
		uint8_t blackCastlingRights = 0;
		int enPassantFile = -1;
		int enPassantRank = -1;
		ColorBit enPassantColor = ColorBit::NOPIECE;
		char* data = fen.data();

		clear();

		int i = 0;
		while (i < fen.size()) {
			char current = data[i];

			switch (state) {
			case 0:
				if (current >= '1' && current <= '8') {
					file += current - '0';
				} else {
					switch (current) {
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
				switch (current) {
				case 'w':
					sideToMove = ColorBit::WHITE;
					i++; // the following character is guaranteed to be a space
					state++;
					break;
				case 'b':
					sideToMove = ColorBit::BLACK;
					i++; // the following character is guaranteed to be a space
					state++;
					break;
				}
				break;
			case 2:
				switch (current) {
				// no case for '-', since the next character is guaranteed to be ' ' in that case, and the ' ' case will set the castling rights bits in the appropriate squares to the appropriate value
				case 'K': // white short castle
					whiteCastlingRights |= 32;
					break;
				case 'Q': // white long castle
					whiteCastlingRights |= 64;
					break;
				case 'k':
					blackCastlingRights |= 32;
					break;
				case 'q':
					blackCastlingRights |= 64;
					break;
				case ' ':
					setCastlingRights(kingIndex(ColorBit::WHITE), (CastlingRightsBit)whiteCastlingRights);
					setCastlingRights(kingIndex(ColorBit::BLACK), (CastlingRightsBit)blackCastlingRights);
					
					state++;
					break;
				}
				
				break;
			case 3:
				if (current >= 'a' && current <= 'h') {
					enPassantFile = current - 'a';
				} else {
					switch (current) {
					// no case for '-', since the next character is guaranteed to be ' ' in that case, and the ' ' case will place the en passant pawn on the appropriate square, if one exists
					// i can include cases to set the rank here, because en passant spawns can only ever appear on one of two ranks
					case '3':
						enPassantColor = ColorBit::WHITE;
						enPassantRank = 2;
						break;
					case '6':
						enPassantColor = ColorBit::BLACK;
						enPassantRank = 5;
						break;
					case ' ':
						if (enPassantColor == ColorBit::NOPIECE || enPassantRank == -1 || enPassantFile == -1) {
							state++;
							break;
						}

						makePiece(enPassantRank * 8 + enPassantFile, PieceTypeBit::EN_PASSANT_PAWN, enPassantColor);
						state++;
						break;
					}
				}

				break;
			}

			if (state > 3) {
				return;
			}

			i++;
		}
	}
	
	std::string Board::rawView() {
		std::stringstream rawViewStream;
		rawViewStream << "(Note: Ranks are drawn in reverse order in raw view)" << std::endl;

		for (int i = 0; i < NUM_SQUARES; i++) {
			rawViewStream << (int)(squares[i]) << "|";
			if (i != 0 && i % 8 == 7) {
				rawViewStream << std::endl;
			}
		}

		return rawViewStream.str();
	}

	std::string Board::pieceToString(int index) {
		if (index < 0 || index >= NUM_SQUARES) {
			return "None";
		}

		if (!isPieceHere(index)) {
			return "None";
		}

		std::stringstream pieceStream;

		pieceStream << "Color: " << bitToString(getColor(index));
		PieceTypeBit type = getPieceType(index);
		pieceStream << " | Type: " << bitToString(type);
		if (type == PieceTypeBit::KING) {
			pieceStream << " | " << bitToString(getInCheck(index));
			pieceStream << " | " << bitToString(getCastlingRights(index));
		}

		return pieceStream.str();
	}

	int Board::material(ColorBit color) {
		int result = 0;
		
		for (int i = 0; i < NUM_SQUARES; i++) {
			if (!isPieceHere(i)) {
				continue;
			}

			if (getColor(i) != color) {
				continue;
			}

			switch (getPieceType(i)) {
			case PieceTypeBit::PAWN:
				result += 1;
				break;
			case PieceTypeBit::KNIGHT:
				result += 3;
				break;
			case PieceTypeBit::BISHOP:
				result += 3;
				break;
			case PieceTypeBit::ROOK:
				result += 5;
				break;
			case PieceTypeBit::QUEEN:
				result += 9;
				break;
			// king has invaluable material, and en passant pawns don't count
			}
		}

		return result;
	}

	void Board::evaluatePosition(int& whiteScore, int& blackScore) {
		whiteScore = 0;
		blackScore = 0;

		for (int i = 0; i < 64; i++) {
			if (!isPieceHere(i)) {
				continue;
			}

			ColorBit pieceColor = getColor(i);
			PieceTypeBit pieceType = getPieceType(i);
			if (pieceType == PieceTypeBit::EN_PASSANT_PAWN) {
				continue;
			}

			switch (pieceType) {
			case PieceTypeBit::PAWN:
				if (pieceColor == ColorBit::WHITE) {
					whiteScore += 1 * PieceSquareTables::whitePawn[i];
				} else {
					blackScore += 1 * PieceSquareTables::blackPawn[i];
				}
				break;
			case PieceTypeBit::KNIGHT:
				if (pieceColor == ColorBit::WHITE) {
					whiteScore += 3 * PieceSquareTables::whiteKnight[i];
				} else {
					blackScore += 3 * PieceSquareTables::blackKnight[i];
				}
				break;
			case PieceTypeBit::BISHOP:
				if (pieceColor == ColorBit::WHITE) {
					whiteScore += 3 * PieceSquareTables::whiteBishop[i];
				} else {
					blackScore += 3 * PieceSquareTables::blackBishop[i];
				}
				break;
			case PieceTypeBit::ROOK:
				if (pieceColor == ColorBit::WHITE) {
					whiteScore += 5 * PieceSquareTables::whiteRook[i];
				} else {
					blackScore += 5 * PieceSquareTables::blackRook[i];
				}
				break;
			case PieceTypeBit::QUEEN:
				if (pieceColor == ColorBit::WHITE) {
					whiteScore += 9 * PieceSquareTables::whiteQueen[i];
				} else {
					blackScore += 9 * PieceSquareTables::blackQueen[i];
				}
				break;
			case PieceTypeBit::KING:
				if (pieceColor == ColorBit::WHITE) {
					whiteScore += 1 * PieceSquareTables::whiteKing[i];
				} else {
					blackScore += 1 * PieceSquareTables::blackKing[i];
				}
				break;
			}
		}
	}

	bool Board::isPieceHere(int index) const {
		if (index < 0 || index >= NUM_SQUARES) {
			return false;
		}

		return (bool)(squares[index] & PIECE_HERE_MASK);
	}
	
	ColorBit Board::getColor(int index) const {
		if (index < 0 || index >= NUM_SQUARES) {
			return ColorBit::NOPIECE;
		}

		if (!isPieceHere(index)) {
			return ColorBit::NOPIECE;
		}
		return (ColorBit)(squares[index] & COLOR_MASK);
	}

	PieceTypeBit Board::getPieceType(int index) const {
		if (index < 0 || index >= NUM_SQUARES) {
			return PieceTypeBit::NOPIECE;
		}

		if (!isPieceHere(index)) {
			return PieceTypeBit::NOPIECE;
		}
		return (PieceTypeBit)(squares[index] & PIECE_TYPE_MASK);
	}

	InCheckBit Board::getInCheck(int index) const {
		if (index < 0 || index >= NUM_SQUARES) {
			return InCheckBit::NOTKING;
		}

		if (!isPieceHere(index)) {
			return InCheckBit::NOTKING;
		}

		if (getPieceType(index) != PieceTypeBit::KING) {
			return InCheckBit::NOTKING;
		}

		return (InCheckBit)(squares[index] & IN_CHECK_MASK);
	}

	CastlingRightsBit Board::getCastlingRights(int index) const {
		if (index < 0 || index >= NUM_SQUARES) {
			return CastlingRightsBit::NOTKING;
		}

		if (!isPieceHere(index)) {
			return CastlingRightsBit::NOTKING;
		}

		if (getPieceType(index) != PieceTypeBit::KING) {
			return CastlingRightsBit::NOTKING;
		}

		return (CastlingRightsBit)(squares[index] & CASTLING_RIGHTS_MASK);
	}

	void Board::setCastlingRights(int index, CastlingRightsBit rights) {
		if (index < 0 || index >= NUM_SQUARES) {
			return;
		}

		if (!isPieceHere(index)) {
			return;
		}

		if (getPieceType(index) != PieceTypeBit::KING) {
			return;
		}

		squares[index] = (squares[index] & ~CASTLING_RIGHTS_MASK) | (uint8_t)rights;
	}
	
	int Board::kingIndex(ColorBit color) const {
		for (int i = 0; i < NUM_SQUARES; i++) {
			if (!isPieceHere(i)) {
				continue;
			}

			if (getColor(i) != color) {
				continue;
			}

			if (getPieceType(i) == PieceTypeBit::KING) {
				return i;
			}
		}
	}
	
	void Board::makePiece(int index, PieceTypeBit type, ColorBit color) {
		if (index < 0 || index >= NUM_SQUARES) {
			return;
		}

		uint8_t typeVal = (uint8_t)type;
		uint8_t colorVal = (uint8_t)color;
		squares[index] = PIECE_HERE_MASK | typeVal | colorVal;
	}

	char Board::squareChar(int index) const {
		if (index < 0 || index >= NUM_SQUARES) {
			return '?';
		}

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
			case PieceTypeBit::EN_PASSANT_PAWN:
				return '.';
			}

			if ((squares[index] & 1) == 1) {
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