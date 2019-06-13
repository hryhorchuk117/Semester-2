

#include <utility>
#include <vector>

using matr = int[8][8];
using position = std::pair<int, int>;

class figure {
public:
    explicit figure(const std::pair<int, int>&, int);

    virtual int value() const;

    virtual char what() const;

    virtual std::vector<position> allMoves(const matr&, const std::vector<figure*>&) const;

    position pos;
    int color;
    bool moved;
};


class pow : public figure {
public:
    explicit pow(const std::pair<int, int>& pos_, int color_) : figure(pos_, color_) {}

    int value() const override;

    virtual std::vector<position> allMoves(const matr&, const std::vector<figure*>&) const;
};


class knight : public figure {
public:
    explicit knight(const std::pair<int, int>& pos_, int color_) : figure(pos_, color_) {}

    int value() const override;

    char what() const override;

    virtual std::vector<position> allMoves(const matr&, const std::vector<figure*>&) const;
};


class bishop : public figure {
public:
    explicit bishop(const std::pair<int, int>& pos_, int color_) : figure(pos_, color_) {}

    int value() const override;

    char what() const override;

    virtual std::vector<position> allMoves(const matr&, const std::vector<figure*>&) const;
};


class rook : public figure {
public:
    explicit rook(const std::pair<int, int>& pos_, int color_) : figure(pos_, color_) {}

    int value() const override;

    virtual std::vector<position> allMoves(const matr&, const std::vector<figure*>&) const;
};


class queen : public figure {
public:
    explicit queen(const std::pair<int, int>& pos_, int color_) : figure(pos_, color_) {}

    int value() const override;

    virtual std::vector<position> allMoves(const matr&, const std::vector<figure*>&) const;

};


class king : public figure {
public:
    explicit king(const std::pair<int, int>& pos_, int color_) : figure(pos_, color_) {}

    int value() const override;

    virtual std::vector<position> allMoves(const matr&, const std::vector<figure*>&) const;
};