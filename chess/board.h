#include "figure.h"

#include <vector>
#include <utility>

using move = std::pair<std::pair<int,int>, std::pair<int, int>>;

void copy(matr&, const matr&);

std::vector<figure*> copy(const std::vector<figure*>&);

figure* findKing(const std::vector<figure*>&, int);

figure* find(const std::vector<figure*>&, position);

char intToChar(int);

void writeMove(const move&);

int randomInt(int, int);

class board {
public:
    explicit board();

    explicit board(const matr&, const std::vector<figure*>&, int);

    std::vector<std::pair<board, move>> generate() const;

    int mark() const;

    int markBoard(int, int, int);

    move bestMove();

    void makeMove(move);

    bool check();

    matr matrix;
    std::vector<figure*> fig;
    int turn;
};
