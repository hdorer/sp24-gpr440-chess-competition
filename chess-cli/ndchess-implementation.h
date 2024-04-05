#include <iostream>
#include "Board.h"
#include <algorithm>
#include <iterator>

int ndchess_implementation() {
    // Print title
    std::cout << "    ____             _          ____        __     ________    ____\n"
        << "   / __ )_________ _(_)___     / __ \\____  / /_   / ____/ /   /  _/\n"
        << "  / __  / ___/ __ `/ / __ \\   / /_/ / __ \\/ __/  / /   / /    / /  \n"
        << " / /_/ / /  / /_/ / / / / /  / _, _/ /_/ / /_   / /___/ /____/ /   \n"
        << "/_____/_/   \\__,_/_/_/ /_/  /_/ |_|\\____/\\__/   \\____/_____/___/   \n"
        << "-------------------------------------------------------------------" << std::endl;

	/*NDChess::Board board;
    std::cout << board << std::endl;
    std::cout << board.material(NDChess::ColorBit::WHITE) << std::endl;*/

    int* arr = NDChess::PieceSquareTables::blackKing;

    int rank = 7;
    int file = 0;
    for (int i = 0; i < 64; i++) {
        // this code is so weird
        bool endOfRank = i % 8 == 7;

        std::cout << arr[rank * 8 + file];
        std::cout << (i == 63 ? "" : (endOfRank ? ",\n" : ", "));

        file++;
        if (endOfRank) {
            rank--;
            file = 0;
        }
    }
	
	return 0;
}