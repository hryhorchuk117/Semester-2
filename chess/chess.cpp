#include "chess.h"
int i =0;
#include <random>
#include <iostream>
#include <string>
#include <vector>

move convertToMove(const std::string& line1, const std::string& line2) {
    std::vector<int> res;
    std::string line = line1 + line2;
    for (auto item : line) {
        if (item != ' ') {
            switch (item) {
                case 'A': res.push_back(0); break;
                case 'B': res.push_back(1); break;
                case 'C': res.push_back(2); break;
                case 'D': res.push_back(3); break;
                case 'E': res.push_back(4); break;
                case 'F': res.push_back(5); break;
                case 'G': res.push_back(6); break;
                case 'H': res.push_back(7); break;
                default : res.push_back((int)item - 49);
            }
        }
    }

    return {{res[0], res[1]}, {res[2], res[3]}};
}


game::game() {
    first = true;
    end = false;
    playerColor = 0;

    board temp;
    gameBoard = temp;
}

void game::setColor() {
    std::cout << "Choose your color:\n";
    std::cout << "White  -  1:\n";
    std::cout << "Black  - -1:\n";
    std::cout << "Random -  0:\n";

    std::cin >> playerColor;

    if (playerColor == 0) {
        playerColor = randomInt(0, 1);
        if (playerColor == 0) {
            playerColor = -1;
        }
    }
}

void game::makeMove() {

    auto possible = gameBoard.generate();

    if (possible.empty()) {
        end = true;
        if (!gameBoard.check()) {
            std::cout << "Draw\n";
        } else

        if (gameBoard.turn == 1) {
            std::cout << "Black has won\n";
        } else std::cout << "White has won\n";

    } else

    if (gameBoard.turn == playerColor) {
        ++i;
        if (i == 11) {
            ++i;
        }
        bool ok = false;
        move m;
        while (!ok) {
            std::string line1, line2;
            std::cin >> line1 >> line2;
            m = convertToMove(line1, line2);
            auto *f = find(gameBoard.fig, m.first);
            std::vector<position> moves;
            if (gameBoard.matrix[m.first.first][m.first.second] != playerColor) {
                ok = false;
            } else moves = f->allMoves(gameBoard.matrix, gameBoard.fig);

            for (auto &item : moves) {
                if (item == m.second) {
                    ok = true;
                    break;
                }
            }

            if (!ok) {
                std::cout << "This move is not possible!\n";
            }
        }

        auto* changeMoved = find(gameBoard.fig, m.first);
        changeMoved->moved = true;
        gameBoard.makeMove(m);

    } else {
        move m = gameBoard.bestMove();
        gameBoard.makeMove(m);
        writeMove(m);
    }

}

bool game::getEnd() {
    return end;
}