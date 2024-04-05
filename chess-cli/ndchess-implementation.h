#include <iostream>
#include "Board.h"

int ndchess_implementation() {
    // Print title
    std::cout << "    ____             _          ____        __     ________    ____\n"
        << "   / __ )_________ _(_)___     / __ \\____  / /_   / ____/ /   /  _/\n"
        << "  / __  / ___/ __ `/ / __ \\   / /_/ / __ \\/ __/  / /   / /    / /  \n"
        << " / /_/ / /  / /_/ / / / / /  / _, _/ /_/ / /_   / /___/ /____/ /   \n"
        << "/_____/_/   \\__,_/_/_/ /_/  /_/ |_|\\____/\\__/   \\____/_____/___/   \n"
        << "-------------------------------------------------------------------" << std::endl;

	NDChess::Board board;
    board.setPositionFromFen("1r4kR/8/p1q1pBP1/2p1P3/2PpN3/3P4/P4PK1/8 b - - 1 41");
    std::cout << board << std::endl;
    std::cout << board.rawView() << std::endl;
    int whiteScore, blackScore;
    board.evaluatePosition(whiteScore, blackScore);
    std::cout << "White score: " << whiteScore << std::endl << "Black score: " << blackScore << std::endl;
	
	return 0;
}