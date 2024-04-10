#pragma once

#include "Board.h"
#include <iostream>
#include "Move.h"
#include <vector>


int ndchess_implementation() {
    // Print title
    std::cout << "    ____             _          ____        __     ________    ____\n"
        << "   / __ )_________ _(_)___     / __ \\____  / /_   / ____/ /   /  _/\n"
        << "  / __  / ___/ __ `/ / __ \\   / /_/ / __ \\/ __/  / /   / /    / /  \n"
        << " / /_/ / /  / /_/ / / / / /  / _, _/ /_/ / /_   / /___/ /____/ /   \n"
        << "/_____/_/   \\__,_/_/_/ /_/  /_/ |_|\\____/\\__/   \\____/_____/___/   \n"
        << "-------------------------------------------------------------------" << std::endl;

	NDChess::Board board;
    // board.setPositionFromFen("r3k2r/pp3p1b/1np2p1p/3p4/3P1b2/1P2PN2/P4PPP/R2K1B1R w kq - 0 16"); // Nakamara vs. Dmitry after turn 15
    // board.setPositionFromFen("1r6/3k1p2/2pn4/p2p1p2/R2P1P2/1r1K1PP1/3N4/6R1 w - - 0 32"); // Nakamara vs. Dmitry after turn 31
    std::cout << board << std::endl;
    std::cout << board.rawView() << std::endl;
    int whiteScore, blackScore;
    board.evaluatePosition(whiteScore, blackScore);
    std::cout << "White score: " << whiteScore << "\nBlack score: " << blackScore << std::endl;
	
	return 0;
}