#pragma once

#include <iostream>

struct point {
    double xx = 0;
    double yy = 0;
    double zz = 0;

    double distance() const;
};

std::istream& operator >> (std::istream& in, point& p);

std::ostream& operator << (std::ostream& out, const point& p);

bool operator == (const point& lhs, const point& rhs);

bool operator < (const point& lhs, const point& rhs);

bool operator <= (const point& lhs, const point& rhs);

int randomInt(int, int);

point randomPoint();

