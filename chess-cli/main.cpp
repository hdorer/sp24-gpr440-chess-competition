#include <algorithm>
#include "BrainRot.h"
#include "chess-simulator.h"
#include <cstdlib>
#include <functional>
#include "magic_enum/magic_enum.hpp"
#include "PGNBuilder.h"
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


/* function generated by Google Gemini */
bool stringStartsWith(std::string string, std::string prefix) {
    return string.size() >= prefix.size() && std::equal(prefix.begin(), prefix.end(), string.begin());
}

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
            return false;
        case 'b':
            return true;
        case 'r':
            int flip = rand() % 2;
            return flip;
        }
    }
}

bool isGameOver(chess::Board& board, PGNBuilder& pgn) {
    std::pair<chess::GameResultReason, chess::GameResult> result = board.isGameOver();
    if (result.second != chess::GameResult::NONE || result.first != chess::GameResultReason::NONE) {
        board.makeNullMove();
        std::string resultStr = std::string(magic_enum::enum_name(result.second)) + " " + std::string(magic_enum::enum_name(result.first));
        std::cout << "GAME OVER: " << resultStr << " " << board.sideToMove() << std::endl;
        std::cout << "Full PGN: " << pgn << std::endl;
        return true;
    }
    return false;
}

void brainRotMove(ChessSimulator::BrainRot& bot, chess::Board& board, PGNBuilder& pgn, bool saySide = false) {
    chess::Move move = bot.getNextMove(board);
    pgn.addMove(board, move);
    std::string moveStr = chess::uci::moveToSan(board, move);
    if (saySide) {
        std::cout << "Brain Rot's move as " << bot.getSide() << ": " << moveStr << std::endl;
    }
    else {
        std::cout << "Brain Rot's move: " << moveStr << std::endl;
    }

    board.makeMove(move);
}

void setPosition(std::string input, ChessSimulator::BrainRot& bot, chess::Board& board, PGNBuilder& pgn, bool& side) {
    std::string oldFen = board.getFen();
    if(input.length() < std::string("setposition ").length()) {
        std::cout << "No FEN provided!" << std::endl;
        return;
    }
    std::string fen = input.substr(std::string("setposition ").size());
    
    board.setFen(fen);

    if (board.pieces(chess::PieceType::KING, chess::Color::WHITE) == chess::Bitboard(0) || board.pieces(chess::PieceType::KING, chess::Color::WHITE) == chess::Bitboard(0) || board.inCheck()) {
        std::cout << "Invalid FEN!" << std::endl;
        board.setFen(oldFen);
        return;
    }

    // std::cin.ignore();
    side = chooseSide();
    bot.setSide(side);
    std::cout << "Player playing as: " << (side ? "black" : "white") << "\n"
        << "Brain Rot playing as: " << (side ? "white" : "black") << std::endl;

    if (bot.getSide() == board.sideToMove()) {
        brainRotMove(bot, board, pgn);
    }
}

void evaluatePosition(ChessSimulator::BrainRot& bot, chess::Board& board) {
    float whiteScore, blackScore;
    bot.evaluatePosition(board, whiteScore, blackScore);
    std::cout << "White score: " << whiteScore << "\nBlack score: " << blackScore << std::endl;
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

    ChessSimulator::BrainRot bot;
    chess::Board board(chess::constants::STARTPOS);
    CLISettings settings;
    PGNBuilder pgn;

    settings.changePlaySelf();

    bool side = settings.playSelf ? true : chooseSide();
    bot.setSide(side);
    std::cout << "Player playing as: " << (side ? "black" : "white") << "\n"
        << "Brain Rot playing as: " << (side ? "white" : "black") << std::endl;

    if (side && !settings.playSelf) {
        brainRotMove(bot, board, pgn);
    }

    std::cin.ignore();

    while (true) {
        if (!settings.playSelf) {
            std::string input;

            std::cout << board << std::endl;
            std::cout << "Input move or command: ";
            getline(std::cin, input);

            if (input == "") {
                continue;
            }
            if (input == "exit") {
                return 0;
            }
            if (input == "settings") {
                settings.menu();
                std::cin.ignore();
                continue;
            }
            if (stringStartsWith(input, "setposition")) {
                setPosition(input, bot, board, pgn, side);
                std::cin.ignore();
                continue;
            }
            if (input == "evaluate") {
                evaluatePosition(bot, board);
                continue;
            }

            try {
                chess::Move playerMove = chess::uci::parseSan(board, input);
                pgn.addMove(board, playerMove);
                board.makeMove(playerMove);
            }
            catch (chess::uci::SanParseError e) {
                std::cout << "Invalid SAN!" << std::endl;
                continue;
            }

            if (isGameOver(board, pgn)) {
                return 0;
            }

            brainRotMove(bot, board, pgn);
            if (isGameOver(board, pgn)) {
                return 0;
            }
        }
        else {
            brainRotMove(bot, board, pgn, true);
            if (isGameOver(board, pgn)) {
                return 0;
            }

            side = !side;
            bot.setSide(side);
        }
    }
}