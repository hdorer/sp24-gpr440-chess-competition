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
    board.setPositionFromFen("r1bqrnk1/2p3p1/np1p1p2/pN1Pp1p1/1PP1P3/P3B1PP/3Q1PB1/R4RK1 w - - 2 21");
    std::cout << board << std::endl;
	
	return 0;
}