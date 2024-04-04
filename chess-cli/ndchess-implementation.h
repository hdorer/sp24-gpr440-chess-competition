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
    
    std::reverse(std::begin(NDChess::PieceSquareTables::blackPawn), std::end(NDChess::PieceSquareTables::blackPawn));

    for (int i = 0; i < 64; i++) {
        std::cout << NDChess::PieceSquareTables::blackPawn[i] << " ";
    }
	
	return 0;
}