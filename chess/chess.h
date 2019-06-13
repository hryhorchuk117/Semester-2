#include "board.h"

#include <string>

move convertToMove(const std::string&);


class game {
public:

    explicit game();

    void setColor();

    void makeMove();

    bool getEnd();

private:
    board gameBoard;
    int playerColor;
    bool end;
    bool first;
};