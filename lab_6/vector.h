#pragma once

#include "point.h"

#include <vector>
#include <algorithm>

using iter = std::vector<point>::iterator;

class vec{
public:
    vec();

    void append(point);

    void insert(iter, point);

    void addRandom(int);

    void erase(point);

    iter find(point);

    std::vector<iter> find(point, double);

    void print();

    void printInOrder();

    template <class func>
    void special(func f) {
        std::vector<std::pair<iter, point>> copy;

        for (auto it = begin(vect); it < end(vect); ++it) {
            copy.emplace_back(it, *it);
        }

        std::sort(begin(copy), end(copy),
                  [](const std::pair<iter, point>& lhs, const std::pair<iter, point>& rhs)
                  { return lhs.second < rhs.second; });

        for (auto item : copy) {
            f(item.first);
        }
    }

    std::vector<point> getVec();

private:
    std::vector<point> vect;
};