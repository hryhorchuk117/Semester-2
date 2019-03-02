#pragma once

#include <vector>
#include "point.h"

using std::vector;

class Vector {
public:

    void Append(Point p) {
        vec.push_back(p);
    }

    void Insert(Point p, int k) {
        vec.insert(begin(vec) + k, p);
    }

    void Remove(int k) {
        vec.erase(begin(vec) + k);
    }

    Point Get(int k) {
        return vec[k];
    }

    unsigned long Length() {
        return vec.size();
    }

    void Print() {
        for (const auto& item : vec) {
            std::cout << item << std::endl;
        }
    }

private:
    vector<Point> vec;
};