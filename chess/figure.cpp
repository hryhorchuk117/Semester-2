#include "figure.h"

bool in(std::pair<int, int> pos) {
    return pos.first >=0 && pos.first < 8 && pos.second >=0 && pos.second < 8;
}


void operator ++ (std::pair<int, int>& pos) {
    ++pos.first;
    ++pos.second;
}

void operator + (std::pair<int, int>& pos) {
    --pos.first;
    ++pos.second;
}

void operator - (std::pair<int, int>& pos) {
    ++pos.first;
    --pos.second;
}

void operator -- (std::pair<int, int>& pos) {
    --pos.first;
    --pos.second;
}

figure::figure(const std::pair<int, int>& pos_, int color_) {
    pos = pos_;
    color = color_;
    moved = false;
}

int figure::value() const {
    return 0;
}

int pow::value() const {
    return 1;
}


int knight::value() const {
    return 3;
}

int bishop::value() const {
    return 3;
}

int rook::value() const {
    return 5;
}

int queen::value() const {
    return 9;
}

int king::value() const {
    return 1000;
}

char figure::what() const {
    return 'f';
}

char knight::what() const {
    return 'n';
}

char bishop::what() const {
    return 'b';
}


std::vector<position> figure::allMoves(const matr& matrix, const std::vector<figure*>& fig) const {
    return {};
}

std::vector<position> pow::allMoves(const matr& matrix, const std::vector<figure*>& fig) const {
    std::vector<position> res;
    position currPos = pos;

    if (color == 1) {
        ++currPos.second;
        if (matrix[currPos.first][currPos.second] == 0) {
            res.push_back(currPos);
            ++currPos.second;
            if (matrix[currPos.first][currPos.second] == 0) {
                res.push_back(currPos);
            }
        }
        currPos = pos;

        +currPos;
        if (in(currPos) && matrix[currPos.first][currPos.second] == color * -1) {
            res.push_back(currPos);
        }
        currPos = pos;

        ++currPos;
        if (in(currPos) && matrix[currPos.first][currPos.second] == color * -1) {
            res.push_back(currPos);
        }
        currPos = pos;

    }

  if (color == -1) {
      --currPos.second;
      if (matrix[currPos.first][currPos.second] == 0) {
          res.push_back(currPos);
          --currPos.second;
          if (matrix[currPos.first][currPos.second] == 0) {
              res.push_back(currPos);
          }
      }
      currPos = pos;

      -currPos;
      if (in(currPos) && matrix[currPos.first][currPos.second] == color * -1) {
          res.push_back(currPos);
      }
      currPos = pos;

      --currPos;
      if (in(currPos) && matrix[currPos.first][currPos.second] == color * -1) {
          res.push_back(currPos);
      }
      currPos = pos;

  }

  return res;

}

std::vector<position> knight::allMoves(const matr& matrix, const std::vector<figure*>& fig) const {

    std::vector<position> res;

    if (in({pos.first + 1, pos.second + 2}) && matrix[pos.first + 1][pos.second + 2] != color) {
        res.emplace_back(pos.first + 1, pos.second + 2);
    }

    if (in({pos.first + 1, pos.second - 2}) && matrix[pos.first + 1][pos.second - 2] != color) {
        res.emplace_back(pos.first + 1, pos.second - 2);
    }

    if (in({pos.first - 1, pos.second + 2}) && matrix[pos.first - 1][pos.second + 2] != color) {
        res.emplace_back(pos.first - 1, pos.second + 2);
    }

    if (in({pos.first - 1, pos.second - 2}) && matrix[pos.first - 1][pos.second - 2] != color) {
        res.emplace_back(pos.first - 1, pos.second - 2);
    }

    if (in({pos.first + 2, pos.second + 1}) && matrix[pos.first + 2][pos.second + 1] != color) {
        res.emplace_back(pos.first + 2, pos.second + 1);
    }

    if (in({pos.first + 2, pos.second - 1}) && matrix[pos.first + 2][pos.second - 1] != color) {
        res.emplace_back(pos.first + 2, pos.second - 1);
    }

    if (in({pos.first - 2, pos.second + 1}) && matrix[pos.first - 2][pos.second + 1] != color) {
        res.emplace_back(pos.first - 2, pos.second + 1);
    }

    if (in({pos.first - 2, pos.second - 1}) && matrix[pos.first - 2][pos.second - 1] != color) {
        res.emplace_back(pos.first - 2, pos.second - 1);
    }

    return res;
}


std::vector<position> bishop::allMoves(const matr& matrix, const std::vector<figure*>& fig) const {
    std::vector<position> res;
    position currPos = pos;

    ++currPos;
    while(in(currPos) && matrix[currPos.first][currPos.second] != color) {
        res.push_back(currPos);
        ++currPos;
    }
    currPos = pos;

    +currPos;
    while(in(currPos) && matrix[currPos.first][currPos.second] != color) {
        res.push_back(currPos);
        +currPos;
    }
    currPos = pos;

    -currPos;
    while(in(currPos) && matrix[currPos.first][currPos.second] != color) {
        res.push_back(currPos);
        -currPos;
    }
    currPos = pos;

    --currPos;
    while(in(currPos) && matrix[currPos.first][currPos.second] != color) {
        res.push_back(currPos);
        --currPos;
    }

    return res;
}


std::vector<position> rook::allMoves(const matr& matrix, const std::vector<figure*>& fig) const {
    std::vector<position> res;
    position currPos = pos;

  ++currPos.first;
  while(in(currPos) && matrix[currPos.first][currPos.second] != color) {
    res.push_back(currPos);
    ++currPos.first;
  }
  currPos = pos;

  ++currPos.second;
  while(in(currPos) && matrix[currPos.first][currPos.second] != color) {
    res.push_back(currPos);
    ++currPos.second;
  }
  currPos = pos;

  --currPos.first;
  while(in(currPos) && matrix[currPos.first][currPos.second] != color) {
    res.push_back(currPos);
    --currPos.first;
  }
  currPos = pos;

  --currPos.second;
  while(in(currPos) && matrix[currPos.first][currPos.second] != color) {
    res.push_back(currPos);
    --currPos.second;
  }

  return res;
}

std::vector<position> queen::allMoves(const matr& matrix, const std::vector<figure*>& fig) const {
  bishop bish(pos, color);
  rook r(pos, color);

  auto resBishop = bish.allMoves(matrix, fig);
  auto resRook = r.allMoves(matrix, fig);

  for (const auto& item : resRook) {
      resBishop.push_back(item);
  }

  return resBishop;
}

std::vector<position> king::allMoves(const matr& matrix, const std::vector<figure*>& fig) const {
    std::vector<position> res;

  if (in({pos.first + 1, pos.second + 1}) && matrix[pos.first + 1][pos.second + 1] != color) {
      res.emplace_back(pos.first + 1, pos.second + 1);
  }

  if (in({pos.first + 1, pos.second}) && matrix[pos.first + 1][pos.second] != color) {
      res.emplace_back(pos.first + 1, pos.second);
  }

  if (in({pos.first, pos.second + 1}) && matrix[pos.first][pos.second + 1] != color) {
      res.emplace_back(pos.first, pos.second + 1);
  }

  if (in({pos.first + 1, pos.second - 1}) && matrix[pos.first + 1][pos.second - 1] != color) {
      res.emplace_back(pos.first + 1, pos.second - 1);
  }

  if (in({pos.first, pos.second - 1}) && matrix[pos.first][pos.second - 1] != color) {
      res.emplace_back(pos.first, pos.second - 1);
  }

  if (in({pos.first - 1, pos.second - 1}) && matrix[pos.first - 1][pos.second - 1] != color) {
      res.emplace_back(pos.first - 1, pos.second - 1);
  }

  if (in({pos.first - 1, pos.second}) && matrix[pos.first - 1][pos.second] != color) {
      res.emplace_back(pos.first - 1, pos.second);
  }

  if (in({pos.first - 1, pos.second + 1}) && matrix[pos.first - 1][pos.second + 1] != color) {
      res.emplace_back(pos.first - 1, pos.second + 1);
  }

  if (!moved) {
      for (const auto& item : fig) {
          if (item->value() == 5 && item->color == color && !item->moved) {
              if (item->pos.first > pos.first) {
                  bool possible = true;
                  for (int i = pos.first + 1; i < item->pos.first; ++i) {
                      if (matrix[i][pos.second] != 0) {
                          possible = false;
                      }
                  }
                  if (possible) {
                      res.emplace_back(pos.first + 2, pos.second);
                  }
              }

              if (item->pos.first < pos.first) {
                  bool possible = true;
                  for (int i = pos.first - 1; i > item->pos.first; --i) {
                      if (matrix[i][pos.second] != 0) {
                          possible = false;
                      }
                  }
                  if (possible) {
                      res.emplace_back(pos.first - 2, pos.second);
                  }
              }
          }

      }
  }

  return res;
}

