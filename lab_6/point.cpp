#include "point.h"

#include <iostream>
#include <tuple>
#include <cmath>
#include <random>

double point::distance() const {
    return sqrt(xx*xx + yy*yy + zz*zz);
}

std::istream& operator >> (std::istream& in, point& p) {
    in >> p.xx >> p.yy >> p.zz;
    return in;
}

std::ostream& operator << (std::ostream& out, const point& p) {
    out << p.xx << " " << p.yy << " " << p.zz;
    return out;
}

bool operator == (const point& lhs, const point& rhs) {
    return std::tie(lhs.xx, lhs.yy, lhs.zz) == std::tie(rhs.xx, rhs.yy, rhs.zz);
}

bool operator < (const point& lhs, const point& rhs) {
    return lhs.distance() > rhs.distance();
}

bool operator <= (const point& lhs, const point& rhs) {
    return lhs < rhs || lhs == rhs;
}

int randomInt(int begin, int end) {
    static std::random_device rd;
    static std::mt19937_64 gen(rd());
    std::uniform_int_distribution<> dis(begin, end);
    return dis(gen);
}

point randomPoint() {
    double x = (double)randomInt(-100000, 100000) / 100;
    double y = (double)randomInt(-100000, 100000) / 100;
    double z = (double)randomInt(-100000, 100000) / 100;

    return {x, y, z};
}