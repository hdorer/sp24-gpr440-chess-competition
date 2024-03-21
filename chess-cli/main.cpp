#include "chess-simulator.h"
#include "chess.hpp"
#include <string>

int main() {
    BrainRot bot;
    std::string fen;
    getline(std::cin, fen);
    std::string move = bot.getNextMove(fen);
    std::cout << move << std::endl;
}