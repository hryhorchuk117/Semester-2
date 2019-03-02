#pragma once
#include "point.h"

const int MAX_SIZE = 100000;

class Array {
public:
    void Append(Point p) {
        if (length == MAX_SIZE) {
            throw ("error");
        }

        arr[length] = p;
        ++length;
    }

    void Insert(Point p, int k) {
        if (length == MAX_SIZE || k > length || k < 0) {
            throw ("error");
        }

        ++length;
        for (int i = length; i > k; --i) {
            arr[i] = arr[i - 1];
        }
       arr[k] = p;
    }

    void Remove(int k) {
        if (length == 0 || k < 0 || k >= length) {
           throw ("error");
        }
        for (int i = k; i < length; ++i) {
            arr[i] = arr[i + 1];
        }
        --length;
    }

    Point Get(int k) {
        if (length == 0 || k < 0 || k >= length) {
            throw ("error");
        }
        return arr[k];
    }

    int Length() {
        return length;
    }

    void Print() {
        for (int i = 0; i < length; ++i) {
            std::cout << arr[i] << std::endl;
        }
    }

private:
    Point arr[MAX_SIZE];
    int length = 0;
};