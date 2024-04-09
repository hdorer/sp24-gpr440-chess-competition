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
    board.setPositionFromFen("1r4kR/8/p1q1pBP1/2p1P3/2PpN3/3P4/P4PK1/8 b - - 1 41");
    std::cout << board << std::endl;
    std::vector<NDChess::Move> legalMoves = board.legalMoves(NDChess::ColorBit::WHITE);
    for (int i = 0; i < legalMoves.size(); i++) {
        std::cout << "[" << i << "]: " << legalMoves[i].moveString << std::endl;
    }
	
	return 0;
}