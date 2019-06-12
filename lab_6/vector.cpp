#include "vector.h"

#include <vector>
#include <algorithm>
#include <utility>
#include <iostream>

vec::vec() {
    this->vect = {};
}

void vec::append(point p) {
    vect.push_back(p);
}

void vec::insert(iter it, point p) {
    vect.insert(it, p);
}

void vec::addRandom(int k) {
    for (int i = 0; i < k; ++i) {
        vect.push_back(randomPoint());
    }
}

void vec::erase(point p) {
    vect.erase(find(p));
}

iter vec::find(point p) {
    return std::find(begin(vect), end(vect), p);
}

std::vector<iter> vec::find(point p, double mistake) {
    std::vector<iter> res;
    for (auto it = begin(vect); it < end(vect); ++it) {
        if (mistake > std::max((*it).distance() - p.distance(), p.distance() - (*it).distance())) {
            res.push_back(it);
        }
    }
    return res;
}

void vec::print() {
    for (auto item : vect) {
        std::cout << item << "\n";
    }
}

void vec::printInOrder() {
    std::vector<point> copy = vect;
    std::sort(begin(copy), end(copy));
    for (auto item : copy) {
        std::cout << item << "\n";
    }
}

std::vector<point> vec::getVec() {
  return vect;
}

/*template <class func>
void vec::special(func f) {
    std::vector<std::pair<iter, point>> copy;

    for (auto it = begin(vect); it < end(vect); ++it) {
        copy.push_back({it, *it});
    }

    std::sort(begin(copy), end(copy),
            [](const std::pair<iter, point>& lhs, const std::pair<iter, point>& rhs)
            { return lhs.second < rhs.second; });

    for (auto [it, trash] : copy) {
        f(it);
    }
}*/