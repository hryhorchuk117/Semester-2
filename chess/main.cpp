#include "chess.h"

int main() {

    game chess;
    chess.setColor();

    while (!chess.getEnd()) {
        chess.makeMove();
    }
    return 0;
}