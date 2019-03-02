#pragma once

struct Point {
    double xx = 0;
    double yy = 0;
    double zz = 0;
};

std::istream& operator >> (std::istream& in, Point& p) {
    in >> p.xx >> p.yy >> p.zz;
    return in;
}

std::ostream& operator << (std::ostream& out, const Point& p) {
    out << p.xx << " " << p.yy << " " << p.zz;
    return out;
}