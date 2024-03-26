#include "chess-simulator.h"
#include "chess.hpp"
#include <string>
#include "magic_enum/magic_enum.hpp"


struct CLISettings {
    bool playSelf = false;

    void menu() {
        while (true) {
            std::cout << "BRAIN ROT CLI SETTINGS" << std::endl;
            std::cout << "*p*lay Self: " << (playSelf ? "true" : "false") << std::endl;
            std::cout << "*b*ack" << std::endl;
            std::cout << "> ";

            char input;
            std::cin >> input;

            switch (input) {
            case 'p':
                changePlaySelf();
                break;
            case 'b':
                return;
            }
        }
    }

    void changePlaySelf() {
        std::cout << "Should Brain Rot play itself? (y/n) > ";

        while (true) {
            char input;
            std::cin >> input;

            switch (input) {
            case 'y':
                playSelf = true;
                return;
            case 'n':
                playSelf = false;
                return;
            }

            std::cout << "> ";
        }
    }
};


int main() {
    // Print title
    std::cout << "    ____             _          ____        __     ________    ____\n"
        << "   / __ )_________ _(_)___     / __ \\____  / /_   / ____/ /   /  _/\n"
        << "  / __  / ___/ __ `/ / __ \\   / /_/ / __ \\/ __/  / /   / /    / /  \n"
        << " / /_/ / /  / /_/ / / / / /  / _, _/ /_/ / /_   / /___/ /____/ /   \n"
        << "/_____/_/   \\__,_/_/_/ /_/  /_/ |_|\\____/\\__/   \\____/_____/___/   " << std::endl;

    BrainRot bot;
    CLISettings settings;
    chess::Board board("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");

    while (true) {
        std::string input;
        
        if (!settings.playSelf) {
            std::cout << "Input FEN: ";
            getline(std::cin, input);
        }

        if (input == "exit") {
            return 0;
        }
        if (input == "settings") {
            settings.menu();
            std::cin.ignore();
            continue;
        }

        if (settings.playSelf) {
            chess::Move move = bot.getNextMove(board);
            std::string moveStr = chess::uci::moveToSan(board, move);
            std::cout << "Brain Rot's move as " << board.sideToMove() << ": " << moveStr << std::endl;

            board.makeMove(move);

            std::pair<chess::GameResultReason, chess::GameResult> result = board.isGameOver();
            if (result.second != chess::GameResult::NONE || result.first != chess::GameResultReason::NONE) {
                std::string resultStr = std::string(magic_enum::enum_name(result.second)) + " " + std::string(magic_enum::enum_name(result.first));
                std::cout << "GAME OVER: " << resultStr << std::endl;
                return 0;
            }
        } else {
            board = chess::Board(input);
            chess::Move move = bot.getNextMove(input);
            std::string moveStr = chess::uci::moveToSan(board, move);
            std::cout << "Brain Rot's move: " << moveStr << std::endl;
        }
    }
}