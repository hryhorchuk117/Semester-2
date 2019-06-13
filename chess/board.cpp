#include "board.h"

#include <algorithm>
#include <iostream>
#include <random>

const int MAX_STEP = 2;


int randomInt(int begin, int end) {
  std::random_device rd;
  std::mt19937_64 gen(rd());
  std::uniform_int_distribution<> dis(begin, end);
  return dis(gen);
}

board::board() {
    for (int i = 0; i < 8; ++i) {
      for (int j = 0; j < 8; ++j) {
        matrix[i][j] = 0;
      }
    }

    for (int j = 0; j < 2; ++j) {
      for (int i = 0; i < 8; ++i) {
        matrix[i][j] = 1;
      }
    }

    for (int j = 7; j > 5; --j) {
      for (int i = 0; i < 8; ++i) {
        matrix[i][j] = -1;
      }
    }

    auto* k = new king({4,0}, 1);
    fig.push_back(k);
    auto* r1 = new rook({0, 0}, 1);
    fig.push_back(r1);
    auto* r2 = new rook({7, 0}, 1);
    fig.push_back(r2);
    auto* b1 = new bishop({2, 0}, 1);
    fig.push_back(b1);
    auto* b2 = new bishop({5, 0}, 1);
    fig.push_back(b2);
    auto* k1 = new knight({1, 0}, 1);
    fig.push_back(k1);
    auto* k2 = new knight({6, 0}, 1);
    fig.push_back(k2);
    auto* q = new queen({3, 0}, 1);
    fig.push_back(q);



    for (int i = 0; i < 8; ++i) {
      auto* p = new class pow({i, 1}, 1);
      fig.push_back(p);
    }

    auto* bk = new king({4,7}, -1);
    fig.push_back(bk);
    auto* br1 = new rook({0, 7}, -1);
    fig.push_back(br1);
    auto* br2 = new rook({7, 7}, -1);
    fig.push_back(br2);
    auto* bb1 = new bishop({2, 7}, -1);
    fig.push_back(bb1);
    auto* bb2 = new bishop({5, 7}, -1);
    fig.push_back(bb2);
    auto* bk1 = new knight({1, 7}, -1);
    fig.push_back(bk1);
    auto* bk2 = new knight({6, 7}, -1);
    fig.push_back(bk2);
    auto* bq = new queen({3, 7}, -1);
    fig.push_back(bq);

    for (int i = 0; i < 8; ++i) {
      auto* bp = new class pow({i, 6}, -1);
      fig.push_back(bp);
    }


    turn = 1;
}

std::vector<figure*> findRooks(const std::vector<figure*>& fig, int color) {
    std::vector<figure*> res;
    for (auto item : fig) {
        if (item->value() == 5 && item->color == color) {
            res.push_back(item);
        }
    }
    return res;
}

board::board(const matr& matrix_, const std::vector<figure*>& fig_,  int turn_) {
    copy(matrix, matrix_);
    fig = fig_;
    turn = turn_;
}


std::vector<figure*> copy(const std::vector<figure*>& vec) {
  std::vector<figure*> res;
  for (const auto& fig : vec) {
    switch (fig->value()) {

    case 1 : {
      auto newPow = new class pow(fig->pos, fig->color);
      res.push_back(newPow);
      break;
    }

    case 3 : {
      if (fig->what() == 'n') {
        auto newKnight = new knight(fig->pos, fig->color);
        res.push_back(newKnight);
      } else {
        auto newBishop = new bishop(fig->pos, fig->color);
        res.push_back(newBishop);
      }
      break;
    }

    case 5 : {
      auto newRook = new rook(fig->pos, fig->color);
      res.push_back(newRook);
      break;
    }

    case 9 : {
      auto newQueen = new queen(fig->pos, fig->color);
      res.push_back(newQueen);
      break;
    }

    case 1000 : {
      auto newKing = new king(fig->pos, fig->color);
      res.push_back(newKing);
      break;
    }

    }
  }

  return res;

}

void copy(matr& lhs, const matr& rhs) {
  for (int i = 0; i < 8; ++i) {
    for (int j = 0; j < 8; ++j) {
      lhs[i][j] = rhs[i][j];
    }
  }
}

figure* find(const std::vector<figure*>& vec, position pos) {
    for (auto item : vec) {
        if (item->pos == pos) {
            return item;
        }
    }

    return nullptr;
}

figure* findKing(const std::vector<figure*>& vec, int color) {
    for (auto item : vec) {
        if (item->value() > 9 && item->color == color) {
            return item;
        }
    }

    return nullptr;
}

std::vector<std::pair<board, move>> board::generate() const {
  std::vector<std::pair<board, move>> res;


  for (auto& currFigure : fig) {
      if (currFigure->color == turn) {
          position start = currFigure->pos;
          auto moves = currFigure->allMoves(matrix, fig);

          for (auto currMove : moves) {
              board afterMove(matrix, copy(fig), turn);
              auto* movedFig = find(afterMove.fig, currFigure->pos);

              if (afterMove.matrix[currMove.first][currMove.second] == movedFig->color * -1) {
                  auto *delFig = find(afterMove.fig, currMove);
                  for (auto it = begin(afterMove.fig); it < end(afterMove.fig); ++it) {
                      if (*it == delFig) {
                          afterMove.fig.erase(it);
                          break;
                      }
                  }
              }

              /*
              if (movedFig->value() > 9 && abs(movedFig->pos.first - currMove.first) > 1) {

                  if (movedFig->pos.first < currMove.first) {
                      auto rooks = findRooks(afterMove.fig, afterMove.turn);
                      auto rookCastle = find(afterMove.fig, {movedFig->pos.first + 3, movedFig->pos.second});
                      afterMove.matrix[rookCastle->pos.first][rookCastle->pos.second] = 0;
                      rookCastle->pos.first -= 2;
                      afterMove.matrix[rookCastle->pos.first][rookCastle->pos.second] = 1;
                  } else {
                      auto rookCastle = find(afterMove.fig, {movedFig->pos.first - 4, movedFig->pos.second});
                      afterMove.matrix[rookCastle->pos.first][rookCastle->pos.second] = 0;
                      rookCastle->pos.first += 3;
                      afterMove.matrix[rookCastle->pos.first][rookCastle->pos.second] = 1;
                  }
              }*/

                  afterMove.matrix[movedFig->pos.first][movedFig->pos.second] = 0;
                  movedFig->pos = currMove;
                  afterMove.matrix[movedFig->pos.first][movedFig->pos.second] = movedFig->color;


                  afterMove.turn *= -1;
                  res.emplace_back(afterMove, std::make_pair(start, currMove));



          }
      }
  }


  for (auto [currBoard, currMove] : res) {
      for (auto item : currBoard.fig) {
          if (item->value() == 1 && (item->pos.second == 0 || item->pos.second == 7)) {
              for (auto it = begin(currBoard.fig); it < end(currBoard.fig); ++it) {
                  if (*it == item) {
                      auto* newQueen = new queen(item->pos, item->color);
                      currBoard.fig.push_back(newQueen);
                      currBoard.fig.erase(it);
                      break;
                  }
              }
          }
      }
  }

  std::vector<std::pair<board, move>> finalRes;
  for (auto [currBoard, currMove] : res) {
      bool check = false;
      auto* kingCheck = findKing(currBoard.fig, turn);

      for (auto item : currBoard.fig) {
          if (item->color != turn) {
              auto attacked = item->allMoves(currBoard.matrix, currBoard.fig);

              for (auto point : attacked) {
                  if (point == kingCheck->pos) {
                      check = true;
                      break;
                  }
              }

              if (check) {
                  break;
              }
          }
      }

      if (!check) {
          finalRes.emplace_back(currBoard, currMove);
      }
  }

  return finalRes;
}

int board::mark() const {
    int count = 0;
    for (auto item : fig) {
        count += item->value() * item->color;
    }
    return count;
}

bool board::check() {
    auto* kingCheck = findKing(fig, turn);

    for (auto item : fig) {
        if (item->color != turn) {
            auto attacked = item->allMoves(matrix, fig);
            for (auto point : attacked) {
                if (point == kingCheck->pos) {
                    return true;
                }
            }
        }
    }
  return false;
}


int board::markBoard(int currStep, int maxStep, int currTurn) {
    auto allBoards = generate();

    if (allBoards.empty() && check()) {
        return 10000 * currTurn * -1;
    }

    if (allBoards.empty() && !check()) {
        return 0;
    }

    if (currStep == maxStep) {
        return mark();
    }

    int count = 0;

    for (auto [currBoard, currMove] : allBoards) {
        int currMark = currBoard.markBoard(currStep + 1, maxStep, currTurn * -1);
        if (currMark * currTurn > count) {
            count = currMark;
        }
    }

    return count;
}

move board::bestMove() {
    auto allBoards = generate();
    std::vector<int> marks;

    int min = 100000;
    for (auto& item : allBoards) {
        int count = item.first.markBoard(0, MAX_STEP, turn);
        marks.push_back(count);
        if (count < min) {
            min = count;
        }
    }

    std::vector<move> res;
    for (int i = 0; i < marks.size(); ++i) {
        if (marks[i] == min) {
            res.push_back(allBoards[i].second);
        }
    }
    return res[randomInt(0, res.size() - 1)];
}

void board::makeMove(move m) {
    auto* movedFig = find(fig, m.first);
    movedFig->moved = true;

    if (matrix[m.second.first][m.second.second] == movedFig->color * -1) {
        auto *delFig = find(fig, m.second);
        for (auto it = begin(fig); it < end(fig); ++it) {
            if (*it == delFig) {
                fig.erase(it);
                break;
            }
        }
    }

    if (movedFig->value() > 9 && abs(movedFig->pos.first - m.second.first) > 1) {

        if (movedFig->pos.first < m.second.first) {
            auto rookCastle = find(fig, {movedFig->pos.first + 3, movedFig->pos.second});
            matrix[rookCastle->pos.first][rookCastle->pos.second] = 0;
            rookCastle->pos.first -= 2;
            matrix[rookCastle->pos.first][rookCastle->pos.second] = 1;
        } else {
            auto rookCastle = find(fig, {movedFig->pos.first - 4, movedFig->pos.second});
            matrix[rookCastle->pos.first][rookCastle->pos.second] = 0;
            rookCastle->pos.first += 3;
            matrix[rookCastle->pos.first][rookCastle->pos.second] = 1;
        }
    }

    matrix[movedFig->pos.first][movedFig->pos.second] = 0;
    movedFig->pos = m.second;
    matrix[movedFig->pos.first][movedFig->pos.second] = movedFig->color;

    turn *= -1;
}

char intToChar(int n) {
  switch (n) {
  case 0 : return 'A';
  case 1 : return 'B';
  case 2 : return 'C';
  case 3 : return 'D';
  case 4 : return 'E';
  case 5 : return 'F';
  case 6 : return 'G';
  case 7 : return 'H';
  default: return ' ';
  }
}

void writeMove(const move& m) {
  std::cout << intToChar(m.first.first);
  std::cout << m.first.second + 1;
  std::cout << ' ';
  std::cout << intToChar(m.second.first);
  std::cout << m.second.second + 1;
  std::cout << '\n';
}
