#include "chess-simulator.h"
#include "chess.hpp"
#include <string>

int main() {
    // Print title
    std::cout << "    ____             _          ____        __     ________    ____\n"
        << "   / __ )_________ _(_)___     / __ \\____  / /_   / ____/ /   /  _/\n"
        << "  / __  / ___/ __ `/ / __ \\   / /_/ / __ \\/ __/  / /   / /    / /  \n"
        << " / /_/ / /  / /_/ / / / / /  / _, _/ /_/ / /_   / /___/ /____/ /   \n"
        << "/_____/_/   \\__,_/_/_/ /_/  /_/ |_|\\____/\\__/   \\____/_____/___/   " << std::endl;

    BrainRot bot;

    while (true) {
        std::cout << "Input FEN: ";
        std::string input;
        getline(std::cin, input);

        if (input == "exit") {
            exit(0);
        }

        std::string move = bot.getNextMove(input);
        std::cout << "Brain Rot's move: " << move << std::endl;
    }
}