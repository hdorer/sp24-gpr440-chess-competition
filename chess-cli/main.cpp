#include "chess-simulator.h"
#include "chess.hpp"
#include <cstdlib>
#include "magic_enum/magic_enum.hpp"
#include <string>


struct CLISettings {
    bool playSelf = false;

    void menu() {
        while (true) {
            std::cout << "BRAIN ROT CLI SETTINGS\n"
                << "*p*lay Self: " << (playSelf ? "true" : "false") << "\n"
                << "*b*ack\n"
                << "> ";

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


bool chooseSide() {
    while (true) {
        std::cout << "*w*hite\n"
            << "*b*lack\n"
            << "*r*andom\n"
            << "Play as which side? > ";
        char choice;
        std::cin >> choice;
        switch (choice) {
        case 'w':
            return true;
        case 'b':
            return false;
        case 'r':
            int flip = rand() % 2;
            return flip;
        }
    }
}

void brainRotMove(BrainRot& bot, chess::Board& board) {
    chess::Move move = bot.getNextMove(board);
    std::string moveStr = chess::uci::moveToSan(board, move);
    std::cout << "Brain Rot's move: " << moveStr << std::endl;

    board.makeMove(move);
}

int main() {
    srand(time(NULL));

    // Print title
    std::cout << "    ____             _          ____        __     ________    ____\n"
        << "   / __ )_________ _(_)___     / __ \\____  / /_   / ____/ /   /  _/\n"
        << "  / __  / ___/ __ `/ / __ \\   / /_/ / __ \\/ __/  / /   / /    / /  \n"
        << " / /_/ / /  / /_/ / / / / /  / _, _/ /_/ / /_   / /___/ /____/ /   \n"
        << "/_____/_/   \\__,_/_/_/ /_/  /_/ |_|\\____/\\__/   \\____/_____/___/   \n"
        << "-------------------------------------------------------------------" << std::endl;

    BrainRot bot;
    CLISettings settings;
    chess::Board board(chess::constants::STARTPOS);

    bool side = chooseSide();

    std::cout << "Player playing as: " << (side ? "black" : "white") << "\n"
        << "Brain Rot playing as: " << (side ? "white" : "black") << std::endl;

    if (side) {
        brainRotMove(bot, board);
    }

    std::cin.ignore();

    while (true) {
        if (!settings.playSelf) {
            std::string input;

            std::cout << board << std::endl;
            std::cout << "Input move or command: ";
            getline(std::cin, input);

            if (input == "exit") {
                return 0;
            }
            if (input == "settings") {
                settings.menu();
                std::cin.ignore();
                continue;
            }

            try {
                chess::Move playerMove = chess::uci::parseSan(board, input);
                board.makeMove(playerMove);
            } catch (chess::uci::SanParseError e) {
                std::cout << "Invalid SAN!" << std::endl;
                continue;
            }

            brainRotMove(bot, board);
        } else {
            brainRotMove(bot, board);
        }

        std::pair<chess::GameResultReason, chess::GameResult> result = board.isGameOver();
        if (result.second != chess::GameResult::NONE || result.first != chess::GameResultReason::NONE) {
            std::string resultStr = std::string(magic_enum::enum_name(result.second)) + " " + std::string(magic_enum::enum_name(result.first));
            std::cout << "GAME OVER: " << resultStr << std::endl;
            return 0;
        }
    }
}